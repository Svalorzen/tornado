#include "lua_map.hpp"

#include <Diluculum/LuaValue.hpp>
#include <Diluculum/LuaExceptions.hpp>

#include <map/map.hpp>

#include <iostream>

LuaMap::LuaMap(const Diluculum::LuaValueList &) : ownMap_(nullptr) {}

LuaMap::LuaMap(const Map * map) : ownMap_(map) {}

Diluculum::LuaValueList LuaMap::isThereFood(const Diluculum::LuaValueList & in) {
    Diluculum::LuaValueList out;
    out.push_back(ownMap_->isThereFood());
    return out;
}

Diluculum::LuaValueList LuaMap::getNearestFood(const Diluculum::LuaValueList & in) {
    Diluculum::LuaValueList out;
    // Check that we got somebody's ID to check for closeness
    if ( in.size() == 0 || in[0].type() != LUA_TNUMBER )
        throw Diluculum::LuaTypeError("ERROR: Didn't get unit ID\n");

    // This will probably need to be updated if we use more types than persons (getThinkable?)
    auto & p = ownMap_->getPerson(static_cast<ID_t>(in[0].asNumber()));

    // We need a pointer because we can't do a nice if with a reference
    const Item * food;

    if ( in.size() == 1 || in[1] == Diluculum::Nil ) {
        food = &(ownMap_->getNearestFood(p.getPosition()));
    }
    else if ( in[1].type() == LUA_TNUMBER ) {
        food = &(ownMap_->getNearestFood(p.getPosition(), static_cast<ID_t>(in[1].asNumber())));
    }
    else {
        throw Diluculum::LuaTypeError("ERROR: Wrong type of info passed");
    }

    out.push_back(food->getId());
    return out;
}
