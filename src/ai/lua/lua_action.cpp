#include "lua_action.hpp"

#include <map/utils/position.hpp>
#include <ai/utils/entity_box.hpp>

#include <string>

LuaAction::LuaAction(const Diluculum::LuaValueList & in) : ownMap_(nullptr) {}
LuaAction::LuaAction(const Map * m, const Person * p) : ownMap_(m), ownPerson_(p) {}

void LuaAction::setAction (const Diluculum::LuaValueList & in) {
    // CHECK IF WE ARE PASSING AN EMPTY LIST
    if ( in[0] == Diluculum::Nil ) {
        std::cout << "ERROR: Passing NO Action" << std::endl;
        return -1;
    }

    // SET ACTIONS

    Diluculum::LuaValueMap action = in[0];

    if ( action["type"] == "move_to" ) {            // MOVE TO - Complete
        int x = std::stoi(action["x"]);
        int y = std::stoi(action["y"]);
        
        Position targetPos(x,y);

        ownAction_.setActionType(MOVE_TO);
        ownAction_.setTargetPosition(targetPos);
    
    } else if ( action["type"] == "pick_up" ) {     // PICK UP - Find a way to put Person position
        if ( action["target"] == "food" ) {
            EntityBox targetBox = ownMap_.getNearestFood(ownPerson_.getPosition());
        }

        ownAction_.setActionType(PICK_UP);
        ownAction_.setEntityBox(targetBox);

    } else if ( action["type"] == "eat" ) {         // EAT
        ownAction_.setActionType(EAT);
        
    } else if ( action["type"] == "put_down" ) {    // PUT DOWN
        ownAction_.setActionType(PUT_DOWN);
    
    } else if ( action["type"] == "sleep" ) {       // SLEEP
        ownAction_.setActionType(SLEEP);    
    
    } else if ( action["type"] == "shelter" ) {     // FIND SHELTER
        ownAction_.setActionType(SHELTER);
    }

}

Action LuaAction::getAction() {
    return ownAction_;
}
