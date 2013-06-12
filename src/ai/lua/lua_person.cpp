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
                n[i] >= Person::NEED_PRIORITIES[j] ) j++;
   
        switch(j) {
            case 0:
                map[Person::NEEDS[i].name] = "verylow";
                break;
            case 1:
                map[Person::NEEDS[i].name] = "low";
                break;
            case 2:
                map[Person::NEEDS[i].name] = "normal";
                break;
            case 3:
                map[Person::NEEDS[i].name] = "max";
                break;
            default:
                break;
        }
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

Diluculum::LuaValueList LuaPerson::getId(const Diluculum::LuaValueList &) {
    Diluculum::LuaValueList list;

    list.push_back(ownPerson_->getId());

    return list;
}

Diluculum::LuaValueList LuaPerson::getResult(const Diluculum::LuaValueList &) {
    Diluculum::LuaValueList out;

    auto & result = ownPerson_->getResult();

    Diluculum::LuaValueMap map;

    // Here we report the results of our last move
    switch ( result.getActionType() ) {
        case ActionType::PICK_UP:
            map["type"] = "pick_up";
            map["targetId"] = result.getTargetId();
            break;
        case ActionType::MOVE_TO:
            map["type"] = "move_to";
            break;
        default:
            map["type"] = "none";
    }

    out.push_back(map);

    return out;
}
