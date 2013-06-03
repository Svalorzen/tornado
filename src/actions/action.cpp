#include "action.hpp"

Action::Action(Entity& e, ActionType t) : entity_(e), at_(t), targetPosition_(), targetEntity_(nullptr) {} 
Action::Action(Entity& e, ActionType t, Position p) : entity_(e), at_(t), targetPosition_(p), targetEntity_(nullptr) {} 
Action::Action(Entity& e, ActionType t, Entity * te) : entity_(e), at_(t), targetPosition_(), targetEntity_(te) {} 

ActionType Action::getActionType() const {
    return at_;
}

Entity & Action::getEntity() {
    return entity_;
}

bool Action::isResolved() const {
    return resolved_;
}

void Action::setResolved(bool r) {
    resolved_ = r;
}

Position Action::getTargetPosition() const {
    return targetPosition_;
}

void Action::setTargetPosition(Position p) {
    targetPosition_ = p;
}

Entity* Action::getTargetEntity() {
    return targetEntity_;
}

void Action::setTargetEntity(Entity* e) {
    targetEntity_ = e;
}
