#include "entity.hpp"

#include <graphics/globals.hpp>

Entity::Entity(Position p) : AnimatedSprite() {
    setPosition(p);
}
Entity::Entity(Position p, const sf::Texture & t) : AnimatedSprite(t) {
    setPosition(p);
}
Entity::Entity(Position p, const sf::Texture & t, const sf::IntRect & r) : AnimatedSprite(t,r) {
    setPosition(p);
}

void Entity::setPosition(Position p) {
    position_ = p;
    AnimatedSprite::setPosition((float)(std::get<X>(position_)*Graphics::TILE_EDGE_SIZE), 
                                (float)(std::get<Y>(position_)*Graphics::TILE_EDGE_SIZE));   
    AnimatedSprite::resize( std::get<W>(position_)*Graphics::TILE_EDGE_SIZE,
                            std::get<H>(position_)*Graphics::TILE_EDGE_SIZE);
}

Entity::Position Entity::getPosition() {
    return position_;
}
