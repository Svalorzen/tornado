#include "animal.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Animal::Animal() : 
    Entity({"1"}, false, AnimatedSprite(Graphics::getTexture("src/resources/red.png"))) {}

void Animal::stepUpdate() {

}
