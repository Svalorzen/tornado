#ifndef LUA_PERSON_HEADER_FILE
#define LUA_PERSON_HEADER_FILE

class Person;
namespace Diluculum { class LuaValueList; }

class LuaPerson {
    public:
        LuaPerson(const Person *);
        LuaPerson(const Diluculum::LuaValueList &);

        Diluculum::LuaValueList getNeeds(const Diluculum::LuaValueList &);

        Diluculum::LuaValueList isMale(const Diluculum::LuaValueList &);

    private:
        const Person * ownPerson_;
};

#endif
