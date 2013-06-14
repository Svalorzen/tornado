#include "action.hpp"

#include <entities/entity.hpp>

Action::Action() : Action(0) {}
Action::Action(ID_t a) : Action(a, ActionType::NONE) {}
Action::Action(ID_t a, ActionType t) : at_(t), actorEntity_(a) {} 
Action::Action(ID_t a, ActionType t, Position<int> p) : at_(t), targetPosition_(p), actorEntity_(a) {} 
Action::Action(ID_t a, ActionType t, ID_t tr, Position<int> p ) :
        at_(t),
        targetPosition_(p),
        actorEntity_(a),
        targetEntity_(tr){} 

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
void Action::setTargetPosition(Position<int> p) {
    targetPosition_ = p;
}

Position<int> Action::getTargetPosition() const {
    return targetPosition_;
}
// #############
void Action::setActorId(ID_t id) {
    actorEntity_ = id;
}

ID_t Action::getActorId() const {
    return actorEntity_;
}
// #############
void Action::setTargetId(ID_t id) {
    targetEntity_ = id;
}

ID_t Action::getTargetId() const {
    return targetEntity_;
}
// #############
void Action::setTarget(const Entity & e) {
    targetEntity_ = e.getId();
    targetPosition_ = e.getPosition();
}
