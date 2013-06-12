#ifndef LUAMAP_HEADER_FILE
#define LUAMAP_HEADER_FILE


class Map;
#include <Diluculum/LuaValue.hpp>

class LuaMap {
    public:
        LuaMap(const Diluculum::LuaValueList &);
        LuaMap(const Map *);

        Diluculum::LuaValueList isThereFood(const Diluculum::LuaValueList &);
        Diluculum::LuaValueList isThereWood(const Diluculum::LuaValueList &);

    private:
        const Map * ownMap_;

};


#endif
