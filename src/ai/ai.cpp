#include "ai.hpp"

#include <iostream>
#include <Diluculum/LuaWrappers.hpp>

#include <ai/lua/lua_action.hpp>
#include <ai/lua/lua_map.hpp>
#include <ai/lua/lua_person.hpp>

constexpr char AI::mapHubName[];
constexpr char AI::entityHubName[];
constexpr char AI::actionHubName[];

// Lua class declaration
DILUCULUM_BEGIN_CLASS(LuaAction)
    DILUCULUM_CLASS_METHOD(LuaAction, setAction)
DILUCULUM_END_CLASS(LuaAction)

// Lua class declaration
DILUCULUM_BEGIN_CLASS(LuaMap)
    DILUCULUM_CLASS_METHOD(LuaMap, isThereFood)
    DILUCULUM_CLASS_METHOD(LuaMap, isThereWood)
    DILUCULUM_CLASS_METHOD(LuaMap, getNearestFood)
    DILUCULUM_CLASS_METHOD(LuaMap, getNearestWood)
DILUCULUM_END_CLASS(LuaMap)

// Lua class declaration
DILUCULUM_BEGIN_CLASS(LuaPerson)
    DILUCULUM_CLASS_METHOD(LuaPerson, getResult)
    DILUCULUM_CLASS_METHOD(LuaPerson, getNeeds)
    DILUCULUM_CLASS_METHOD(LuaPerson, isMale)
    DILUCULUM_CLASS_METHOD(LuaPerson, getId)
DILUCULUM_END_CLASS(LuaPerson)

AI::AI() {
    // Registering class
    DILUCULUM_REGISTER_CLASS(state_["LuaAction"], LuaAction);
    DILUCULUM_REGISTER_CLASS(state_["LuaMap"], LuaMap);
    DILUCULUM_REGISTER_CLASS(state_["LuaPerson"], LuaPerson);

    // Register memory variable
    state_.doString("memory = {};");
}

AI& AI::getInstance() {
    static AI ai;
    return ai;
}

Diluculum::LuaValue AI::getLuaValue(std::string valueName, std::string fileName) {
    // If we don't have it
    if ( state_[valueName].value() == Diluculum::Nil ) {
        try { state_.doFile(fileName); }
        catch(Diluculum::LuaFileError) { std::cout << "Lua File missing" << std::endl; }
    }

    return state_[valueName].value();
}
