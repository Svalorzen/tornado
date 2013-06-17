#include "building.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Building::Building(Area a, BuildingType t) : Entity(a,false, AnimatedSprite()), type_(t), valid_(false) { 
    if ( t == BuildingType::HOUSE )
        getOwnSprite().setTexture(Graphics::getTexture("src/resources/house.png"));

    getOwnSprite().setColor(sf::Color(0,0,255));
}

BuildingType Building::getType() {
    return type_;
}

void Building::stepUpdate() {}

ID_t Building::getUnbuildableArea() const {
    return unbuildableArea_;
}
void Building::setUnbuildableArea(ID_t id) {
    unbuildableArea_ = id;
}
void Building::validate() {
    setSolid(true);
    getOwnSprite().setColor(sf::Color(255,255,255));
    valid_ = true;
}

bool Building::isValid() const {
    return valid_;
}
