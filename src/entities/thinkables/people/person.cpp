#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>
#include <entities/items/item.hpp>

#include <functional>

//    MAP, AREA, SOLID
Person::Person(const Map & m, bool isMale) : 
    Thinkable(m, {"1"}, false, Graphics::getTexture("src/resources/red.png")), male_(isMale), needs_({10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}) {}

Action Person::getAction() {
    // ARRAY OF ACTIONS FOR EACH LEVEL OF BASIC NEEDS
    //const Action veryLowNeedActions[] = {
    //    Action(*this, ActionType::SLEEP), 
    //    Action(*this, ActionType::PICK_UP, getOwnMap()->getNearestFood(getPosition())),
    //    Action(*this, ActionType::SHELTER)
    //};
   
   //// CHECK FOR ACTIONS
    //const std::function<bool(const Person &)> veryLowControlActions[] = {
    //    [](const Person &){ return true; }, // When very low a person will sleep everywhere
    //    std::bind(&Map::isThereFood,*getOwnMap()),
    //    std::bind(&Map::isThereShelter,*getOwnMap())
    //};

    // 0 SLEEP
    // 1 HUNGER
    // 2 COLD
    
//    for ( size_t i = 0; i < BASIC_NEEDS_NUM; i++ ) {
//        if ( needs_[i] < NEEDS_LOW ) { // VERY LOW
//            if ( 
//                return lowNeedActions[i];
//        } 
//    
//    }

    if ( getOwnMap().isThereFood() ) {
        return Action(*this, ActionType::PICK_UP,getOwnMap().getNearestFood(getPosition()));
    } 
    return Action(*this, ActionType::MOVE_TO, getPosition());
}

void Person::stepUpdate() {
    for ( size_t i = 0; i < NEEDS_NUM; i++ ) {
        needs_[i] -= 1;     
        if ( needs_[i] == 0 ) {
            // DEATH
        }
    }
}

