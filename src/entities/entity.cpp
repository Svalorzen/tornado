#include "entity.hpp"

#include <graphics/globals.hpp>
#include <globals.hpp>

#include <iostream>

ID_t Entity::idCreator_ = 0u;

Entity::Entity(const Position<int>& p, const Area& a, bool s, const AnimatedSprite& spr) : id_(idCreator_), position_(p), area_(a), solid_(s), ownSprite_(spr) {
    idCreator_++;    
    
    // DEBUG
    ownSprite_.setToRender(false);
}
Entity::Entity(const Area& a, bool s, const AnimatedSprite& spr) : Entity({0,0}, a,s,spr) {}

ID_t Entity::getId() const {
    return id_;
}

void Entity::setPosition(const Position<int>& p) {
    stepDiff_ = p - position_;
    position_ = p;
}

const Position<int> & Entity::getPosition() const {
    return position_;
}

const Distance<int> & Entity::getStepDiff() const {
    return stepDiff_;
}

void Entity::setArea(const Area& a) {
    area_ = a;
}

const Area & Entity::getArea() const {
    return area_;
}

void Entity::setSolid(bool s) {
    solid_ = s;
}

bool Entity::isSolid() const {
    return solid_;
}

void Entity::setOwnSprite(const AnimatedSprite & spr) {
    ownSprite_ = spr;
}

AnimatedSprite & Entity::getOwnSprite() {
    return ownSprite_;
}

const AnimatedSprite & Entity::getOwnSprite() const {
    return ownSprite_;
}

void Entity::refresh() {
    ownSprite_.setPosition( (float)position_.getX()*Graphics::TILE_EDGE_SIZE, 
                            (float)(position_.getY()-area_.getMaxH()+1)*Graphics::TILE_EDGE_SIZE);
    ownSprite_.resize(      area_.getMaxW()*Graphics::TILE_EDGE_SIZE,
                            area_.getMaxH()*Graphics::TILE_EDGE_SIZE);

    stepDiff_ = {0,0}; 
}

void Entity::graphicalUpdate(unsigned msLapsed) {
    // The entity counts as in position_ for all game effects,
    // here we are simply visualizing the transition.
    float stepPercentage = 1.0f - (float)msLapsed / Core::MS_PER_UPDATE;
    ownSprite_.setPosition( ((float)position_.getX()-stepPercentage*stepDiff_.getDiffXi())*Graphics::TILE_EDGE_SIZE, 
                            ((float)(position_.getY()-area_.getMaxH()+1)-stepPercentage*stepDiff_.getDiffYi())*Graphics::TILE_EDGE_SIZE);
}

std::vector<ID_t> & Entity::getInventory() {
    return inventory_;
}

const std::vector<ID_t> & Entity::getInventory() const {
    return inventory_;
}
