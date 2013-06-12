#include "lua_action.hpp"

#include <map/map.hpp>

#include <Diluculum/LuaValue.hpp>
#include <Diluculum/LuaExceptions.hpp>

#include <map/utils/position.hpp>
#include <entities/thinkable.hpp>

#include <string>
#include <iostream>

LuaAction::LuaAction(const Diluculum::LuaValueList & in) : ownMap_(nullptr) {}
LuaAction::LuaAction(const Map * m, const Thinkable * p) : ownMap_(m), ownEntity_(p), ownAction_(p->getId()) {}

Diluculum::LuaValueList LuaAction::setAction(const Diluculum::LuaValueList & in) {
    // CHECK IF WE ARE PASSING AN EMPTY LIST
    if ( in.size() == 0 || in[0] == Diluculum::Nil || in[0].type() != LUA_TTABLE ) {
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
    
    } else if ( action["type"].asString() == "pick_up" ) {     // PICK UP
        ownAction_.setActionType(ActionType::PICK_UP);
        if ( action["target"].asString() == "food" || action["target"].asString() == "wood" ) {
            // This maybe works for things other than wood
            auto & target = ownMap_->getItem(static_cast<ID_t>(action["targetId"].asNumber()));
            ownAction_.setTarget(target);
        }
        // Last case in which we have no idea what to target
        else {
            throw std::runtime_error("We don't have a target to pickup!\n");
        }
    } else if ( action["type"].asString() == "eat" ) {         // EAT
        ownAction_.setActionType(ActionType::EAT);
        
    } else if ( action["type"].asString() == "put_down" ) {    // PUT DOWN
        ownAction_.setActionType(ActionType::PUT_DOWN);
    
    } else if ( action["type"].asString() == "sleep" ) {       // SLEEP
        ownAction_.setActionType(ActionType::SLEEP);    
    
    } else if ( action["type"].asString() == "shelter" ) {     // FIND SHELTER
        ownAction_.setActionType(ActionType::SHELTER);

    } else if ( action["type"].asString() == "build" ) {
        ownAction_.setActionType(ActionType::BUILD);
    }
    // else if type none .... nothing to do!

    return Diluculum::LuaValueList();
}

Action LuaAction::getAction() {
    return ownAction_;
}
