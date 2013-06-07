#include "lua_action.hpp"

#include <map/map.hpp>

#include <Diluculum/LuaValue.hpp>
#include <Diluculum/LuaExceptions.hpp>

#include <map/utils/position.hpp>
#include <ai/utils/entity_box.hpp>
#include <entities/entity.hpp>

#include <string>
#include <iostream>

LuaAction::LuaAction(const Diluculum::LuaValueList & in) : ownMap_(nullptr) {}
LuaAction::LuaAction(const Map * m, const Entity * p) : ownMap_(m), ownEntity_(p) {}

Diluculum::LuaValueList LuaAction::setAction(const Diluculum::LuaValueList & in) {
    // CHECK IF WE ARE PASSING AN EMPTY LIST
    if ( in[0] == Diluculum::Nil || in[0].type() != LUA_TTABLE ) {
        throw Diluculum::LuaTypeError("ERROR: Wrong type of info passed");
    }

    // SET ACTIONS
    Diluculum::LuaValue actionValue = in[0];
    auto action = actionValue.asTable();

    if ( action["type"].asString() == "move_to" ) {            // MOVE TO - Complete
        int x = static_cast<int>(action["x"].asNumber());
        int y = static_cast<int>(action["y"].asNumber());
        
        Position targetPos(x,y);

        ownAction_.setActionType(ActionType::MOVE_TO);
        ownAction_.setTargetPosition(targetPos);
    
    } else if ( action["type"].asString() == "pick_up" ) {     // PICK UP - Find a way to put Entity position
        ownAction_.setActionType(ActionType::PICK_UP);
        if ( action["target"].asString() == "food" ) {
            ownAction_.setEntityBox(ownMap_->getNearestFood(ownEntity_->getPosition()));
        }


    } else if ( action["type"].asString() == "eat" ) {         // EAT
        ownAction_.setActionType(ActionType::EAT);
        
    } else if ( action["type"].asString() == "put_down" ) {    // PUT DOWN
        ownAction_.setActionType(ActionType::PUT_DOWN);
    
    } else if ( action["type"].asString() == "sleep" ) {       // SLEEP
        ownAction_.setActionType(ActionType::SLEEP);    
    
    } else if ( action["type"].asString() == "shelter" ) {     // FIND SHELTER
        ownAction_.setActionType(ActionType::SHELTER);
    }
    // else if type none .... nothing to do!

    return Diluculum::LuaValueList();
}

Action LuaAction::getAction() {
    return ownAction_;
}
