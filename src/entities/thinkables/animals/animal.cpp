#include "animal.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

Animal::Animal(const Map & m) : 
    Thinkable(m, {"1"}, false, Graphics::getTexture("src/resources/red.png")) {}

