#include "lua_map.hpp"

LuaMap::LuaMap(const Diluculum::LuaValueList &) : ownMap_(nullptr) {}

LuaMap::LuaMap(const Map & map) : ownMap_(map) {}

Diluculum::LuaValueList LuaMap::isThereFood(const Diluculum::LuaValueList & in) {
    Diluculum::LuaValueList a;
    a.push_back(ownMap_.isThereFood());
    return a;
}

