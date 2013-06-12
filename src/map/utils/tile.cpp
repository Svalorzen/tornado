#include "tile.hpp"

#include <algorithm>
#include <entities/entity.hpp>

Tile::Tile(AnimatedSprite spr) : ownSprite_(spr) , walkable_(true) {}

bool Tile::isWalkable() const {
    return walkable_;
}

void Tile::addEntity(const Entity & e) {
    aboveEntities_.emplace_back(e.getId(), e.isSolid());
    walkable_ |= e.isSolid();
}

void Tile::rmEntity(const Entity & e) {
    walkable_ = true;
    for ( auto it = begin(aboveEntities_); it != end(aboveEntities_); /* NO! it++ */ ) {
        if ( (*it).first == e.getId() )
            it = aboveEntities_.erase(it);
        else {
            walkable_ |= (*it).second;
            it++;
        }
    }
}

const std::vector<std::pair<ID_t,bool>> & Tile::getEntities() const {
    return aboveEntities_;
}

void Tile::setOwnSprite(AnimatedSprite spr) {
    ownSprite_ = spr;
}
AnimatedSprite & Tile::getOwnSprite() {
    return ownSprite_;
}
const AnimatedSprite & Tile::getOwnSprite() const {
    return ownSprite_;
}
