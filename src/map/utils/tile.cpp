#include "tile.hpp"

#include <algorithm>
#include <entities/entity.hpp>

Tile::Tile() : AnimatedSprite() , walkable_(true) {}
Tile::Tile(const sf::Texture & t) : AnimatedSprite(t), walkable_(true) {}
Tile::Tile(const sf::Texture & t, const sf::IntRect & r) : AnimatedSprite(t,r), walkable_(true) {}

bool Tile::isWalkable() const {
    return walkable_;
}

void Tile::addEntity(const Entity * e) {
    aboveEntities_.push_back(e);
    walkable_ |= e->isSolid();
}

void Tile::rmEntity(const Entity * e) {
    walkable_ = true;
    for ( auto it = begin(aboveEntities_); it != end(aboveEntities_); /* NO! it++ */ ) {
        if ( (*it) == e )
            it = aboveEntities_.erase(it);
        else {
            walkable_ |= (*it)->isSolid();
            it++;
        }
    }
}

std::vector<const Entity*> Tile::getEntities() {
    return aboveEntities_;
}
