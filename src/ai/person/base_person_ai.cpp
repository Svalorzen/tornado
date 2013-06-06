#include "base_person_ai.hpp"

#include <entities/person.hpp>
#include <entities/item.hpp>
#include <ai/utils/action.hpp>
#include <map/map.hpp>

#include <iostream>

Action BasePersonAI::getAction(const Person & body) {
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
        return Action(ActionType::PICK_UP,getOwnMap().getNearestFood(body.getPosition()));
    } 
    return Action(ActionType::MOVE_TO, body.getPosition());
}
