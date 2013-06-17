#include "game_engine.hpp"

#include <map/map.hpp>

#include <entities/entity.hpp>
#include <ai/utils/action.hpp>

#include <ai/lua/lua_person.hpp>
#include <ai/lua/lua_action.hpp>
#include <ai/lua/lua_map.hpp>
// These needs to be last!
#include <ai/ai.hpp>

#include <chrono>
#include <iostream>

GameEngine::GameEngine(Map & m) : ownMap_(m) {}

bool GameEngine::runStep() {
    constexpr unsigned HOUSE_COST = 5; 

    auto & people = ownMap_.getPeople();
    std::vector<ID_t> deadPeople;

    AI& ai = AI::getInstance();

    auto cpm = const_cast<const Map *>( & ownMap_ );
    LuaMap lm(cpm);

    // FIXME: This for needs to become a while calling a resolver function onto a person;
    for ( auto & p : people ) {
        // Set people so that graphically they are actually in the square they had to go previous turn,
        // so that there shouldn't be circular turns
        p.refresh();

        // Build constant person pointer
        auto cpp = const_cast<const Person*>( &p );
        // Create Lua wrappers 
        LuaPerson lp(cpp);
        LuaAction la(cpm, cpp);
        // Run Lua AI
        auto action = ai.basePerson(lm, lp, la);

        // CHECK FOR STUFF WE MAY BE LOCKING IF WE CHANGE OUR MIND
        if ( p.isLocking() ) {
            if ( action.getActionType() != ActionType::VALIDATE ) {
                try {
                    auto & building = ownMap_.getBuilding(p.getLocked());
                    if ( p.getId() == building.getOwner() && ! building.isValid() )
                        ownMap_.removeBuilding(building.getId());
                }
                catch ( std::runtime_error ) {}
            }
        }
        
        // We may resolve more than one action at a time, so this checks that
        switch( action.getActionType() ) {
            // ###########################################
            // ############ ITEM PICK UP #################
            // ###########################################
            case ActionType::PICK_UP: {
                Item * tp;
                try {
                    tp = &(ownMap_.getItem(action.getTargetId()));
                } catch ( std::runtime_error e ) {
                    p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                    break;
                }
                Item & target = *tp;
                // If we are not the ones locking, something weird is going on..
                if ( target.isLocked() ) {
                    if ( p.getId() != target.getLocker() )
                        throw std::runtime_error("Picking locked item.\n");
                }
                else {
                    // Free old target
                    if ( p.isLocking() )
                        // FIXME: This probably will need to change (not only item are targets..)
                        ownMap_.getItem(p.getLocked()).unlock();

                    target.lock(p.getId());
                    p.lock(target.getId());
                }
                if ( p.getPosition() == action.getTargetPosition() ) {
                    ownMap_.stashItem(target.getId());
                    p.getInventory().push_back(target.getId());
                    p.unlock();
                    p.setResult(action);
                    break;
                }
                goto MOVE_TO_LABEL;
            }
            // ###########################################
            // ############## BUILD HOME #################
            // ###########################################
            case ActionType::BUILD: {
                // This should be read from the action or something!!
                Area buildArea({"11","11"});
                    
                //std::cout << "Checking building!\n";
                if ( !ownMap_.canBuild(action.getTargetPosition(), buildArea) ) {
                    p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                    break;
                }
                //std::cout << "Can build!\n";

                bool buildHouse = false;
                {
                    auto & inv = p.getInventory();
                    if ( inv.size () >= HOUSE_COST ) {
                        size_t j = inv.size();
                    
                        for ( int i = j-1; i >= 0; i-- ) {
                            if ( ownMap_.getItem(inv[i]).getType() == ItemType::WOOD ) {
                                j--;
                                std::swap(inv[i],inv[j]);
                                if ( inv.size() - j >= HOUSE_COST ) {
                                    buildHouse = true;
                                    break;
                                }
                            }
                        }
                    }

                    if ( !buildHouse ) {
                        p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                        break;
                    }
                }
                //std::cout << "Building!\n";

                auto & b = ownMap_.addBuilding(action.getTargetPosition(), buildArea, BuildingType::HOUSE);
                b.lock(p.getId());
                p.lock(b.getId());

                p.setResult(action);
                
                break;
            }
            // ###########################################
            // ############## VALIDATION #################
            // ###########################################
            case ActionType::VALIDATE: {
                //std::cout << "Validating!\n";
                auto & b = ownMap_.getBuilding(action.getTargetId());
                auto pos = b.getPosition()+Distance<int>(-1, 0);
                if ( p.getPosition() != pos) {
                    action.setTargetPosition(pos);
                    goto MOVE_TO_LABEL;
                }
                else {
                    ownMap_.validateBuilding(b.getId());
                    {
                        auto & inv = p.getInventory();
                        for ( size_t i = inv.size() - 1, j = 0; j < HOUSE_COST; j++, i--)
                            ownMap_.removeItem(inv[i]);

                        inv.erase(end(inv) - HOUSE_COST, end(inv));
                    }
                    p.unlock();
                    b.unlock();

                    p.own(b.getId());
                    b.setOwner(p.getId());

                    p.setResult(action);
                }
                break;
            }
            // ###########################################
            // ############## REPRODUCTION ###############
            // ###########################################
            case ActionType::REPRODUCE: {
                constexpr unsigned REPRODUCTION_COST = 5;
                bool reproduce = false;
                if ( ! p.isOwner() ) {
                    p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                    break;
                }
                auto & inv = p.getInventory();
                if ( p.getNeeds()[value("hunger", Person::NEEDS)] > Person::NEED_PRIORITIES[0] ) {
                    if ( inv.size () >= REPRODUCTION_COST ) {
                        size_t j = inv.size();
                    
                        for ( int i = j-1; i >= 0; i-- ) {
                            if ( ownMap_.getItem(inv[i]).getType() == ItemType::FOOD ) {
                                j--;
                                std::swap(inv[i],inv[j]);
                                if ( inv.size() - j >= REPRODUCTION_COST ) {
                                    reproduce = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if ( reproduce ) {
                    // Remove stuff from map
                    for ( size_t i = inv.size() - 1, j = 0; j < REPRODUCTION_COST; j++, i--)
                        ownMap_.removeItem(inv[i]);
                    // Remove stuff from inventory
                    inv.erase(end(inv) - REPRODUCTION_COST, end(inv));

                    ownMap_.addPerson(p.getPosition());
                    p.setResult(action);

                }
                else {
                    // Failure
                    p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                }
                break;
            }
            // ###########################################
            // ############## MOVEMENT ###################
            // ###########################################
            case ActionType::MOVE_TO: {
                MOVE_TO_LABEL: 
                // std::cout << "ENGINE: Moving - "; p.getPosition().print(); std::cout << " --> ";
                //                                  action.getTargetPosition().print(); std::cout << "\n";
                auto nextMove = computeSingleMove(p, action.getTargetPosition()); 
                if ( nextMove == Position<int>(-1,-1) ) {
                    p.setResult(Action(p.getId(), ActionType::FAILURE)); 
                    std::cout << "Couldn't find any path!" << std::endl;
                    break; 
                }
                // std::cout << "ENGINE: Next move is: "; nextMove.print(); std::cout << "\n";
                // Here there should probably be a check verifying that target position is walkable in the
                // sense that there aren't agents in there, or maybe there is an agent that wants to switch places with us
                // IF ( NOT WALKABLE && ENDPOINT.HAS_ENTITY ) {
                //     RESOLVE(PICK_ENTITY_ON_ENDPOINT)
                // }
                // ELSE {
                    ownMap_.setEntityPosition(p, nextMove);
                    Action actualAction(p.getId(), ActionType::MOVE_TO, nextMove);
                    p.setResult(actualAction);
                // }
                
                break;
            }
            // This is for cases when the luaAction returned failure for some reason
            // We let the AI know
            case ActionType::FAILURE: {
                p.setResult(action);
                break;
            }
            default: {
                p.setResult(Action());
            }
        }
        p.stepUpdate();
        if ( p.getNeeds()[value("hunger", Person::NEEDS)] == 0 ) {
            deadPeople.push_back(p.getId());
            if ( p.isLocking() ) {
                try {
                    auto & building = ownMap_.getBuilding(p.getLocked());
                    if ( ! building.isValid() )
                    ownMap_.removeBuilding(building.getId());
                }
                catch ( std::runtime_error ) {
                    ownMap_.getItem(p.getLocked()).unlock();     
                }
            }
        }
    }
    for ( auto i : deadPeople ) {
        ownMap_.removePerson(i);
    }
    if ( ownMap_.getPeople().size() == 0 )
        return false;
    return true;
}

Position<int> GameEngine::computeSingleMove(const Entity & entity, Position<int> target) {
   // std::cout << "Going to -- "; target.print();
   // std::cout << "From     -- "; entity.getPosition().print();
   // std::cout << "\n";

    if (entity.getPosition() == target) return target;

    // For now we assume everything is walkable
    // This is the pair that allows us to search for already computed paths
    auto definingPair = std::make_pair(&entity, target);

    // IT HERE IS PAIR OF (HASH,VALUE), AND VALUE IS PAIR OF (VECTOR, ITERATOR)
    auto it = cachedPaths_.find(definingPair);
    // If we already have that path
    if ( it != cachedPaths_.end() ) {
        // Moves are stored in inverted order perform better (vector doesn't need to move everything up one step after pop)
        // So if this pathing actually starts from where we are, we can use it
        // NOTE: this check will probably have to be updated to verify that all steps still walk on 
        // walkable tiles (since we may have built stuff in the meantime). Thanksfully we can't destroy stuff
        // so we don't need to trash old paths because a new faster way opened up.
        // Or we may want to validate only the next step, and we recompute the path only when we realize that
        // the world has changed
        if ( (*it).second.first.size() > 1 && entity.getPosition() == (*it).second.first.back() ) {
            auto & grid = ownMap_.getGrid();
            (*it).second.first.pop_back();
            if ( grid[it->second.first.back().getY()][it->second.first.back().getX()].isWalkable() ) {
                // If it is good, we refresh it in the history
                cachedPathsHistory_.splice(cachedPathsHistory_.begin(), cachedPathsHistory_, (*it).second.second);

                return (*it).second.first.back();
            }
        }
        // Otherwise it's wrong (for whatever reason), so we remove it from the history and then recompute it
        cachedPathsHistory_.erase((*it).second.second);
    }

    // Compute path
    std::vector<Position<int>> path;

/*
    auto dist = target - entity.getPosition();

    // NOTE: LAST MOVES IN FIRST, LastInFirstOut!
    {
        int i = 0;
        if ( dist.getDiffXi() < 0 ) {
            while( i >= dist.getDiffXi() ) {
                path.emplace_back(target.getX()-i, target.getY());
                i--;
            }
        }
        else {
            while( i <= dist.getDiffXi() ) {
                path.emplace_back(target.getX()-i, target.getY());
                i++;
            }
        }
        i = 1;
        if ( dist.getDiffYi() < 0 ) {
            i = -i;
            while( i > dist.getDiffYi() ) {
                path.emplace_back(entity.getPosition().getX(), target.getY()-i);
                i--;
            }
        }
        else {
            while( i < dist.getDiffYi() ) {
                path.emplace_back(entity.getPosition().getX(), target.getY()-i);
                i++;
            }
        }

    }

    if ( path.back() == entity.getPosition() )
        path.pop_back();
*/
    // std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // for ( int i = 0; i < 10; i++ )

    path = Astar(entity.getPosition(), target);
    if ( path.size() == 0 )
        return Position<int>(-1,-1);
        
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "\nENGINE: A* TOOK : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << " MILLISECONDS\n\n";
    // FIXME: Astar may fail!
    // {
    // std::cout << "ENGINE: A* PATH:\n";
    // for ( auto p : path ) {
    //     std::cout << "  ";
    //     p.print();
    // }
    // std::cout << "\n\n";
    // }

    // We can build it in a forward manner, but then we have to invert it.
    // std::reverse(path.begin(),path.end());

    // Updating cache history
    cachedPathsHistory_.push_front(definingPair);

    // Save path (iterator to element should remain valid throughout)
    cachedPaths_[definingPair] = std::make_pair(path,cachedPathsHistory_.begin());

    // Cleaning cache
    if ( cachedPaths_.size() > MAX_PATH_CACHE ) {
        cachedPaths_.erase(cachedPathsHistory_.back());
        cachedPathsHistory_.pop_back();
    }

    // Return path step
    return path.back();
}
