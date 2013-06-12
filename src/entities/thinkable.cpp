#include "thinkable.hpp"

void Thinkable::setResult(Action a) {
    result_ = a;
}

const Action & Thinkable::getResult() const {
    return result_;
}
