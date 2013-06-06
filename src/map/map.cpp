#include "map.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <ai/utils/action.hpp>
#include <ai/utils/entity_box.hpp>
#include <ai/person/base_person_ai.hpp>

Map::Map(int x, int y) {
    // getTexture MAY THROW! 
    const sf::Texture & texture = Graphics::getTexture("src/resources/green.png");

    std::vector<Tile> dummy;
    // Reserve space in advance
    dummy.reserve(x);
    grid_.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(texture);
            dummy.back().setPosition(j*Graphics::TILE_EDGE_SIZE, i*Graphics::TILE_EDGE_SIZE);
        }
        grid_.push_back(dummy);
        dummy.clear();
    }

    people_.reserve(1000);
    items_.reserve(1000);

    addPerson({1,1});
}

void Map::runStep() { 
    std::vector<std::pair<Action, Person&>> actions;

    BasePersonAI ai(*this);

    for ( auto & p : people_ ) {
        actions.emplace_back(ai.getAction(p), p);
        // Set people so that graphically they are actually in the square they had to go previous turn,
        // so that there shouldn't be circular turns
        p.refresh();
    }

    for ( auto & a : actions ) {
        // We may resolve more than one action at a time, so this checks that
        if ( ! a.first.isResolved() ) {
            switch( a.first.getActionType() ) {
                case ActionType::PICK_UP: {
                    if ( a.second.getPosition() == a.first.getTargetPosition() ) {
                        removeItem(a.first.getEntityBox().getEntityIndex());
                        //for ( auto it = begin(items_) ; it != end(items_); it ++ ) {
                        //    if ( &(*it) == a.getTargetEntity() ) {
                        //        std::cout << "DELETED!!\n";
                        //        items_.erase(it);
                        //        break;
                        //    }
                        //}

                        break;
                    }
                // FALL THROUGH IF THEY ARE NOT IN THE SAME POSITION
                }
                case ActionType::MOVE_TO: {
                    auto nextMove = computeSingleMove(a.second, a.first.getTargetPosition()); 
                    // Here there should probably be a check verifying that target position is walkable in the
                    // sense that there aren't agents in there, or maybe there is an agent that wants to switch places with us
                    setEntityPosition(a.second, nextMove);
                    break;
                }
                default: std::cout << "No code specified for this type of action: "<<(int)a.first.getActionType()<<"\n" ;
            }
        }
    }
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell);
    
    for ( auto & i : items_ ) {
        window.draw(i.getOwnSprite());
        i.graphicalUpdate(elapsedMs);
    }
    for ( auto & p : people_ ) {
        window.draw(p.getOwnSprite());
        p.graphicalUpdate(elapsedMs);
    }
}

void Map::addPerson(Position pos) {
    std::uniform_int_distribution<int> distribution(0,1);
    // Randomizes man females
    people_.emplace_back(distribution(generator_));
    Person & p = people_.back();

    setEntityPosition(p, pos);
    p.refresh();
}

void Map::removePerson(size_t i) {
    unapplyEntityFromGrid(people_[i]);
    people_.erase(begin(people_)+i);
}

void Map::addItem(Position pos) {
    items_.emplace_back(ItemType::FOOD);
    Item & i = items_.back();

    setEntityPosition(i, pos);
    i.refresh();
}

void Map::removeItem(size_t i) {
    unapplyEntityFromGrid(items_[i]);
    items_.erase(begin(items_)+i);
}

Position Map::computeSingleMove(const Entity & entity, Position target) {
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
            // If it is good, we refresh it in the history
            cachedPathsHistory_.splice(cachedPathsHistory_.begin(), cachedPathsHistory_, (*it).second.second);

            (*it).second.first.pop_back();
            return (*it).second.first.back();
        }
        // Otherwise it's wrong (for whatever reason), so we remove it from the history and then recompute it
        else {
            cachedPathsHistory_.erase((*it).second.second);
        }
    }
    std::vector<Position> path;

    // Compute path
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

   // std::cout << "PATH BUILT:\n";
   // for ( auto p : path ) {
   //     std::cout << "  ";
   //     p.print();
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

// This function updates tile links, it is called only when we are actually
// sure the guy will move here
void Map::setEntityPosition(Entity & e, Position p) {
    unapplyEntityFromGrid(e);
    e.setPosition(p);
    applyEntityToGrid(e);
}

bool Map::isThereFood() const {
    for ( auto & i : items_ )
        if ( i.getType() == ItemType::FOOD && ! i.isLocked() ) 
            return true;

    return false;
}

EntityBox Map::getNearestFood(Position p) const {
    int it = -1;
    Distance distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == ItemType::FOOD && ! item.isLocked() ) {
            Distance distanceDiff = p - item.getPosition();

            if ( it == -1 || distance > distanceDiff ) {
                it = i;
                distance = distanceDiff;
            }
        }
    }

    return EntityBox(items_[it], static_cast<size_t>(it));
}

void Map::unapplyEntityFromGrid(const Entity& e) {
    std::vector<Position> initialTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : initialTiles ) {
        try {
            grid_.at(p.getX()).at(p.getY()).rmEntity(&e); 
        } catch(...){}
    }
}

void Map::applyEntityToGrid(const Entity& e) {
    std::vector<Position> finalTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : finalTiles ) {
        try {
            grid_.at(p.getX()).at(p.getY()).addEntity(&e); 
        } catch(...) {}
    }
}
