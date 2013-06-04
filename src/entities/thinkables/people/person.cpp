#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

//    MAP, AREA, SOLID
Person::Person(Map& m, bool isMale) : 
    Thinkable(m, {"1"}, false, Graphics::getTexture("src/resources/red.png")), male_(isMale), needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}

Action Person::getAction() {
    
    const Action veryLowNeedActions[] = {
        Action(*this, ActionType::SLEEP), 
        Action(*this, ActionType::PICK_UP, getOwnMap().getNearestFood(*this)),
        Action(*this, ActionType::SHELTER)
    }
    const Action lowNeedActions[] = {
        Action(*this, ActionType::SLEEP), 
        Action(*this, ActionType::PICK_UP, getOwnMap().getNearestFood(*this)),
        Action(*this, ActionType::SHELTER)
    }
    const Action normalNeedActions[] = {
        Action(*this, ActionType::SLEEP), 
        Action(*this, ActionType::PICK_UP, getOwnMap().getNearestFood(*this)),
        Action(*this, ActionType::SHELTER)
    }
    
    // 0 SLEEP
    // 1 HUNGER
    // 2 COLD
    
    for (int i = 0; i < 3; i++) {
        if ( needs_[i] = 0 ) // TODO: DEATH
    }

    // Check priority basic need (0-Sleep, 1-Hunger, 2-Cold)
    
    for (int i = 0; i < 3; i++) {
        if ( needs_[i] < 2500 ) { // VERY LOW
            return lowNeedActions[i];
        } 
    
    }

}

void Person::stepUpdate() {
}

Map Person::getOwnMap() {
    return 
}
