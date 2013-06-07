#include "ai.hpp"

#include <Diluculum/LuaVariable.hpp>
#include <Diluculum/LuaWrappers.hpp>

#include <ai/lua/lua_map.hpp>
#include <ai/lua/lua_person.hpp>
#include <ai/lua/lua_action.hpp>

namespace AI {
    Action basePerson(LuaMap & m, LuaPerson & p, LuaAction & a) {
        auto ai = getLuaVariable("base_person_ai", "base_person_ai.lua"); 

        if ( ai.type() != LUA_TFUNCTION )
            throw Diluculum::LuaRunTimeError("Couldn't load ai function.");

        // Set current AI with standard name 
        DILUCULUM_REGISTER_OBJECT(state_[mapHubName],    LuaMap,     m);
        DILUCULUM_REGISTER_OBJECT(state_[entityHubName], LuaPerson,  p);
        DILUCULUM_REGISTER_OBJECT(state_[actionHubName], LuaAction,  a);

        state_.call(ai.asFunction(), Diluculum::LuaValueList() );

        return a.getAction();
    }
}
