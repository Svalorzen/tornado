#include "entity.hpp"

#include <graphics/globals.hpp>

Entity::Entity(Position p) : AnimatedSprite(), position(p) {
    AnimatedSprite::setPosition((float)(std::get<X>(position)*Graphics::TILE_EDGE_SIZE),
                                (float)(std::get<Y>(position)*Graphics::TILE_EDGE_SIZE));   
    AnimatedSprite::resize( std::get<W>(position)*Graphics::TILE_EDGE_SIZE,
                            std::get<H>(position)*Graphics::TILE_EDGE_SIZE);
}

void Entity::setPosition(Position p) {
    position = p;
    AnimatedSprite::setPosition((float)(std::get<X>(position)*Graphics::TILE_EDGE_SIZE), 
                                (float)(std::get<Y>(position)*Graphics::TILE_EDGE_SIZE));   
    AnimatedSprite::resize( std::get<W>(position)*Graphics::TILE_EDGE_SIZE,
                            std::get<H>(position)*Graphics::TILE_EDGE_SIZE);
}

