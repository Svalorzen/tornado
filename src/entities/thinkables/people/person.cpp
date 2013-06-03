#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

Person::Person(Map& m, bool isMale) : 
    Thinkable(m, {"1"}, Graphics::getTexture("src/resources/red.png")), male_(isMale), needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}

Action Person::getAction() {
    static int x = 0, y = 0;
    ActionType action;

    if ( x != 2 && y == 0 ) {
        x++;
        action = ActionType::MOVE_RIGHT;
    }
    else if ( x == 2 && y != 2 ) {
        y++;
        action = ActionType::MOVE_DOWN;
    }
    else if ( y == 2 && x != 0 ) {
        x--;
        action = ActionType::MOVE_LEFT;
    }
    else { 
        y--;
        action = ActionType::MOVE_UP;
    }

    return Action(*this, action);
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

