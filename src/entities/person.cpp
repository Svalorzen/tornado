#include "person.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

//    MAP, AREA, SOLID
Person::Person(bool isMale) : 
    Entity({"1"}, false, AnimatedSprite(Graphics::getTexture("src/resources/red.png"))),
    male_(isMale),
    needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}


void Person::stepUpdate() {
    for ( size_t i = 0; i < NEEDS_NUM; i++ ) {
        needs_[i] -= 1;     
        if ( needs_[i] == 0 ) {
            // DEATH
        }
    }
}

