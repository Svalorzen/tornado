#include "entity.hpp"

#include <graphics/globals.hpp>
#include <globals.hpp>

#include <iostream>

Entity::Entity(Map & m, Area a, bool s) : AnimatedSprite(), ownMap_(m), area_(a), solid_(s) {
    refresh();
}
Entity::Entity(Map & m, Area a, bool s, const sf::Texture & t) : AnimatedSprite(t), ownMap_(m), area_(a), solid_(s) {
    refresh();
}
Entity::Entity(Map & m, Area a, bool s, const sf::Texture & t, const sf::IntRect & r) : AnimatedSprite(t,r), ownMap_(m), area_(a), solid_(s) {
    refresh();
}

void Entity::setPosition(Position p) {
    diffPosition_ = p - position_;
    position_ = p;
}

void Entity::refresh() {
    AnimatedSprite::setPosition((float)position_.getX()*Graphics::TILE_EDGE_SIZE, 
                                (float)position_.getY()*Graphics::TILE_EDGE_SIZE);
    AnimatedSprite::resize( area_.getMaxW()*Graphics::TILE_EDGE_SIZE,
                            area_.getMaxH()*Graphics::TILE_EDGE_SIZE);

    diffPosition_ = {0,0}; 
}

void Entity::update(unsigned msLapsed) {
    // The entity counts as in position_ for all game effects,
    // here we are simply visualizing the transition.
    float stepPercentage = 1.0f - (float)msLapsed / Core::MS_PER_UPDATE;
    AnimatedSprite::setPosition(((float)position_.getX()-stepPercentage*diffPosition_.getX())*Graphics::TILE_EDGE_SIZE, 
                                ((float)position_.getY()-stepPercentage*diffPosition_.getY())*Graphics::TILE_EDGE_SIZE);
}

Position Entity::getPosition() const {
    return position_;
}

Area Entity::getArea() const {
    return area_;
}

bool Entity::isSolid() const {
    return solid_;
}
