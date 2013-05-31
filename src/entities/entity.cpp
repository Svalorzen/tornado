#include "entity.hpp"

#include <graphics/globals.hpp>

Entity::Entity(Map & m, Area a) : AnimatedSprite(), ownMap_(m), area_(a) {
    refresh();
}
Entity::Entity(Map & m, Area a, const sf::Texture & t) : AnimatedSprite(t), ownMap_(m), area_(a) {
    refresh();
}
Entity::Entity(Map & m, Area a, const sf::Texture & t, const sf::IntRect & r) : AnimatedSprite(t,r), ownMap_(m), area_(a) {
    refresh();
}

void Entity::setPosition(Position p) {
    position_ = p;
    refresh();
}

void Entity::refresh() {
    AnimatedSprite::setPosition((float)position_.getX()*Graphics::TILE_EDGE_SIZE, 
                                (float)position_.getY()*Graphics::TILE_EDGE_SIZE);
    AnimatedSprite::resize( area_.getMaxW()*Graphics::TILE_EDGE_SIZE,
                            area_.getMaxH()*Graphics::TILE_EDGE_SIZE);
}

Position Entity::getPosition() const {
    return position_;
}

Area Entity::getArea() const {
    return area_;
}
