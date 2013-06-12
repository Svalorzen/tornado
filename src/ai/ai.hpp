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
        static constexpr char mapHubName[]     = "mapHub"; 
        static constexpr char entityHubName[]  = "entityHub"; 
        static constexpr char actionHubName[]  = "actionHub";

        static AI & getInstance();

        Action basePerson(LuaMap &, LuaPerson &, LuaAction &);
    private:
        Diluculum::LuaValue getLuaValue(std::string, std::string);

        AI();
        AI(const AI &) = delete;
        AI & operator=(const AI&) = delete;
        
        Diluculum::LuaState state_;
};

#endif
