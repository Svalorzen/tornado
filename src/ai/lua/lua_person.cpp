#include "lua_person.hpp"

#include <entities/person.hpp>

LuaPerson::LuaPerson(const Person * p) : ownPerson_(p) {}
LuaPerson::LuaPerson(const Diluculum::LuaValueList &) : ownPerson_(nullptr) {}

Diluculum::LuaValueList LuaPerson::getNeeds(const Diluculum::LuaValueList &) {
    Diluculum::LuaValueMap map;
    
    auto n = ownPerson_->getNeeds();

    for ( size_t i = 0; i < size_of(Person::NEEDS); i++ ) {
        size_t j = 0;
        while ( j < size_of(Person::NEED_PRIORITIES) &&
                n[i] > Person::NEED_PRIORITIES[j] ) j++;

        map[Person::NEEDS[i].name] = j;
    }

    Diluculum::LuaValueList list;
    list.push_back(map);

    return list;
}

Diluculum::LuaValueList LuaPerson::isMale(const Diluculum::LuaValueList &) {
    Diluculum::LuaValueList list;

    list.push_back(ownPerson_->isMale());

    return list;
}
