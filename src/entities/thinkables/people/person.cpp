#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

//    MAP, AREA, SOLID
Person::Person(Map& m, bool isMale) : 
    Thinkable(m, {"1"}, false, Graphics::getTexture("src/resources/red.png")), male_(isMale), needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}

Action Person::getAction() {
    static int x = 0, y = 0;
    if ( getPosition().getX() == x && getPosition().getY() == y ) {
        x = (x+6) %10;
        y = (y+13) % 10;
    }
    return Action(*this, ActionType::MOVE_TO, {x,y});
}

void Person::stepUpdate() {
}

unsigned Person::getNeedValue(size_t index) {
    return needs_[index];
}


int Person::getPriorityNeed() {
    size_t priorityNeed = 0;
    
    // CHECK PEOPLE BASIC NEEDS
    for ( int i = 0; i < 3; i++ ) {
    
        if (needs_[i] == 0); // TODO: DEATH
        
        if (needs_[priorityNeed] > needs_[i])
            priorityNeed = i;
        
    }

    return priorityNeed;
}

