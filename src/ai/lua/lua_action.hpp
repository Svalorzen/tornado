#ifndef LUAACTION_HEADER_FILE
#define LUAACTION_HEADER_FILE

#include <ai/utils/action.hpp>

class Map;
namespace Diluculum { class LuaValueList }

class LuaAction {
    public:
        LuaAction(const Diluculum::LuaValueList &);
        LuaAction(const Map * , const Person *);

        void setAction(Action::ActionType);

        Action getAction();

    private:
        const Map * ownMap_;
        const Person * ownPerson_;
        Action ownAction_;      
        
};

#endif
