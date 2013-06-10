#include "thinkable.hpp"

void Thinkable::setLastAction(Action a) {
    lastAction_ = a;
}

Action Thinkable::getLastAction() const {
    return lastAction_;
}
