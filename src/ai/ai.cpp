#include "ai.hpp"

#include <iostream>

#include <Diluculum/LuaState.hpp>
#include <Diluculum/LuaVariable.hpp>

const Diluculum::LuaValue & AI::getLuaVariable(std::string variableName, std::string fileName) {
    // If we don't have it
    if ( state_[variableName].value() == Diluculum::Nil ) {
        try { state_.doFile(fileName); }
        catch(Diluculum::LuaFileError) { std::cout << "Lua File missing" << std::endl; }
    }

    return state_[valueName];
}
