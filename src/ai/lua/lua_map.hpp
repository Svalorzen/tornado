#ifndef LUAMAP_HEADER_FILE
#define LUAMAP_HEADER_FILE

enum class ItemType;
class Map;
#include <Diluculum/LuaValue.hpp>

class LuaMap {
    public:
        LuaMap(const Diluculum::LuaValueList &);
        LuaMap(const Map *);

        Diluculum::LuaValueList isThereFood(const Diluculum::LuaValueList &);
        Diluculum::LuaValueList isThereWood(const Diluculum::LuaValueList &);
        Diluculum::LuaValueList getNearestFood(const Diluculum::LuaValueList &);
        Diluculum::LuaValueList getNearestWood(const Diluculum::LuaValueList &);
    
        Diluculum::LuaValueList getNearestItem(ItemType type, const Diluculum::LuaValueList & in);
    
    private:
        const Map * ownMap_;

};


#endif
