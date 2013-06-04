#include "map.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <entities/entity.hpp>
#include <entities/items/item.hpp>
#include <entities/buildings/building.hpp>
#include <entities/thinkables/people/person.hpp>

#include <actions/action.hpp>

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

    addPerson({1,1});
}

void Map::runStep() { 
    std::vector<Action> actions;
    for ( auto & p : people_ ) {
        actions.push_back(p->getAction());
        // Set people so that graphically they are actually in the square they had to go previous turn,
        // so that there shouldn't be circular turns
        p->refresh();
    }

    for ( auto & a : actions ) {
        // We may resolve more than one action at a time, so this checks that
        if ( ! a.isResolved() ) {
            switch( a.getActionType() ) {
                case ActionType::MOVE_TO: {
                    auto nextMove = computeSingleMove(a.getEntity(), a.getTargetPosition()); 
                    // Here there should probably be a check verifying that target position is walkable in the
                    // sense that there aren't agents in there, or maybe there is an agent that wants to switch places with us
                    setEntityPosition(a.getEntity(), nextMove);
                    break;
                }
                default: std::cout << "No code specified for this type of action: "<<(int)a.getActionType()<<"\n" ;
            }
        }
    }
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell);
    
    for ( auto & e : entities_ ) {
        window.draw(*e);
        e->graphicalUpdate(elapsedMs);
    }
}

void Map::addPerson(Position pos) {
    std::uniform_int_distribution<int> distribution(0,1);
    // Randomizes man females
    std::shared_ptr<Person> p(new Person(*this, distribution(generator_)));
    std::shared_ptr<Entity> e(p);

    setEntityPosition(*p, pos);
    p->refresh();

    people_.push_back(p);
    entities_.push_back(e);
}

void Map::addResource(Position pos) {
    std::shared_ptr<Item> i(new Item(*this, ItemType::FOOD));
    std::shared_ptr<Entity> e(i);

    setEntityPosition(*i, pos);
    i->refresh();

    items_.push_back(i);    
    entities_.push_back(e);
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
    auto diff = target - entity.getPosition();

    // NOTE: LAST MOVES IN FIRST, LastInFirstOut!
    {
        int i = 0;
        if ( diff.getX() < 0 ) {
            while( i >= diff.getX() ) {
                path.emplace_back(target.getX()-i, target.getY());
                i--;
            }
        }
        else {
            while( i <= diff.getX() ) {
                path.emplace_back(target.getX()-i, target.getY());
                i++;
            }
        }
        i = 1;
        if ( diff.getY() < 0 ) {
            i = -i;
            while( i > diff.getY() ) {
                path.emplace_back(entity.getPosition().getX(), target.getY()-i);
                i--;
            }
        }
        else {
            while( i < diff.getY() ) {
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
    {
        std::vector<Position> initialTiles = e.getArea().applyArea(e.getPosition());

        for ( auto & p : initialTiles )
            grid_.at(p.getX()).at(p.getY()).rmEntity(&e); 
    }
    {
        std::vector<Position> finalTiles = e.getArea().applyArea(p);

        for ( auto & p : finalTiles )
            grid_.at(p.getX()).at(p.getY()).addEntity(&e); 
    }
    e.setPosition(p);
}
bool Map::isThereFood() const {
    for ( auto & i : items_ )
        if ( i->getType() == ItemType::FOOD && ! i->isLocked() ) 
            return true;

    return false;
}

const Item * Map::getNearestFood(Position p) const {
    const Item * pi = nullptr;
    int distance = 0;

    for ( auto & i : items_ ) {
        if ( i->getType() == ItemType::FOOD && ! i->isLocked() ) {
            Position diffPos = p - i->getPosition();
            int distanceDiff = abs(diffPos.getX()) + abs(diffPos.getY());

            if ( pi == nullptr || distance > distanceDiff ) {
                pi = i.get();
                distance = distanceDiff;
            }
        }
    }

    return pi;
}
