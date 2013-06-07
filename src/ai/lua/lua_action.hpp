#ifndef LUA_ACTION_HEADER_FILE
#define LUA_ACTION_HEADER_FILE

#include <ai/utils/action.hpp>

class Map;
class Person;
#include <Diluculum/LuaValue.hpp>

class LuaAction {
    public:
        LuaAction(const Diluculum::LuaValueList &);
        LuaAction(const Map * , const Entity *);

        Diluculum::LuaValueList setAction(const Diluculum::LuaValueList&);

        Action getAction();

    private:
        const Map * ownMap_;
        const Entity * ownEntity_;
        Action ownAction_;      
        
};


#endif
