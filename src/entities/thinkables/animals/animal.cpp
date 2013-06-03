#include "animal.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

Animal::Animal(Map& m) : 
    Thinkable(m, {"1"}, Graphics::getTexture("src/resources/red.png")) {}

