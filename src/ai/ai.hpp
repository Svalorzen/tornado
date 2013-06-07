#ifndef AI_HEADER_FILE
#define AI_HEADER_FILE

#include <string>

#include <Diluculum/LuaState.hpp>

class LuaAction;
class LuaMap;
class LuaPerson;
class Action;

class AI {
    public:
        AI();
        static constexpr char mapHubName[]     = "mapHub"; 
        static constexpr char entityHubName[]  = "entityHub"; 
        static constexpr char actionHubName[]  = "actionHub";

        Action basePerson(LuaMap &, LuaPerson &, LuaAction &);
    private:
        Diluculum::LuaValue getLuaValue(std::string, std::string);
        
        Diluculum::LuaState state_;
};

#endif
