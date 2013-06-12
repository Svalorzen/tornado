#include "person.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

// Declaration of static stuff so other people can see it
constexpr entry Person::NEEDS[];
constexpr size_t Person::NEEDS_NUM;
constexpr size_t Person::BASIC_NEEDS_NUM;
constexpr unsigned Person::NEED_PRIORITIES[];


//    MAP, AREA, SOLID
Person::Person(bool isMale) : 
    Thinkable({"1"}, false, AnimatedSprite(Graphics::getTexture("src/resources/red.png"))),
    male_(isMale),
    needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}


void Person::stepUpdate() {
    for ( size_t i = 0; i < NEEDS_NUM; i++ ) {
        needs_[i] -= 1000;     
        if ( needs_[i] == 0 ) {
            // DEATH
        }
    }
}

bool Person::isMale() const {
    return male_;
}

const std::array<unsigned, Person::NEEDS_NUM> & Person::getNeeds() const {
    return needs_;
}
