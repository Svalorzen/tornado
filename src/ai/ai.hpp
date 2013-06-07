#ifndef AI_HEADER_FILE
#define AI_HEADER_FILE

#include <string>

class LuaAction;
class LuaMap;
class LuaPerson;

namespace Diluculum { class LuaVariable; }

class AI {
    public:
        constexpr char mapHubName[]     = "mapHub"; 
        constexpr char entityHubName[]  = "entityHub"; 
        constexpr char actionHubName[]  = "actionHub";

        Action basePerson(LuaMap &, LuaPerson &, LuaAction &);
    private:
        const Diluculum::LuaVariable & getLuaVariable(std::string, std::string);
        
        Diluculum::LuaState state_;
};

#endif
