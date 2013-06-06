#include "building.hpp"

#include <graphics/animated_sprite.hpp>

Building::Building(Area a) : Entity(a,true, AnimatedSprite()) {}

void Building::stepUpdate() {}
