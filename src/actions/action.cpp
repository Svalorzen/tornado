#include "action.hpp"

Action::Action(Entity& e, ActionType t) : entity_(e), at_(t) {} 

ActionType Action::getActionType() const {
    return at_;
}

Entity & Action::getEntity() {
    return entity_;
}

