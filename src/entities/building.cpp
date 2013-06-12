#include "building.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Building::Building(Area a, BuildingType t) : Entity(a,true, AnimatedSprite()), type_(t) {
    
    if ( t == BuildingType::HOUSE )
        getOwnSprite().sf::Sprite::setTexture(Graphics::getTexture("src/resources/house.png"));
}

BuildingType Building::getType() {
    return type_;
}

void Building::stepUpdate() {}
