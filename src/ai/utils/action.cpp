#include "action.hpp"

#include <entities/entity.hpp>

Action::Action(ActionType t) : at_(t) {} 
Action::Action(ActionType t, Position p) : at_(t), targetPosition_(p) {} 
Action::Action(ActionType t, EntityBox te) :
        at_(t),
        targetPosition_(te.getEntity()->getPosition()),
        targetEntity_(te){} 

// #############
void Action::setResolved(bool r) {
    resolved_ = r;
}

bool Action::isResolved() const {
    return resolved_;
}
// #############
void Action::setActionType(ActionType t) {
    at_ = t;
}

ActionType Action::getActionType() const {
    return at_;
}
// #############
void Action::setTargetPosition(Position p) {
    targetPosition_ = p;
}

Position Action::getTargetPosition() const {
    return targetPosition_;
}
// #############
void Action::setEntityBox(EntityBox e) {
    targetEntity_ = e;
}

const EntityBox Action::getEntityBox() const {
    return targetEntity_;
}

