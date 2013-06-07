#ifndef AI_HEADER_FILE
#define AI_HEADER_FILE

namespace AI {
    Action basePerson(const Map &, const Person &);
        
    inline const Diluculum::LuaValue & getLuaValue(std::string fileName, std::string valueName) {
        static Diluculum::LuaState state_;
        
        // If we don't have it
        if ( state_[valueName].value() == Diluculum::Nil ) {
            try { state_.doFile(fileName); }
            catch(Diluculum::LuaFileError) { std::cout << "Lua File missing" << std::endl; }
        }

        return state_[valueName].value();
    }
}

#endif
