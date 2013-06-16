#include "tile.hpp"

#include <algorithm>
#include <entities/entity.hpp>
#include <entities/aoe.hpp>

#include <graphics/textures.hpp>

Tile::Tile(AnimatedSprite spr) : ownSprite_(spr) , walkable_(true), buildable_(true), shelter_(false) {}

bool Tile::isWalkable() const {
    return walkable_;
}
bool Tile::isBuildable() const {
    return buildable_;
}
bool Tile::isShelter() const {
    return shelter_;
}

void Tile::addEntity(const Entity & e) {
    aboveEntities_.emplace_back(e.getId(), e.isSolid());
    walkable_ &= !e.isSolid();
}

void Tile::rmEntity(const Entity & e) {
    walkable_ = true;
    for ( auto it = begin(aboveEntities_); it != end(aboveEntities_); /* NO! it++ */ ) {
        if ( (*it).first == e.getId() )
            it = aboveEntities_.erase(it);
        else {
            walkable_ &= !(*it).second;
            it++;
        }
    }
}

void Tile::addAoE(const AoE & e) {
    aboveAoEs_.emplace_back(e.getId(), e.isBuildable(), e.isShelter());
    buildable_ &= e.isBuildable();
    shelter_ |= e.isShelter();
}

void Tile::rmAoE(const AoE & e) {
    buildable_ = true;
    shelter_ = false;
    for ( auto it = begin(aboveAoEs_); it != end(aboveAoEs_); /* NO! it++ */ ) {
        if ( std::get<0>(*it) == e.getId() )
            it = aboveAoEs_.erase(it);
        else {
            buildable_ &= std::get<1>(*it);
            shelter_ |= std::get<2>(*it);
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
