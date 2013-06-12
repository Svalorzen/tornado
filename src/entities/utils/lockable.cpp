#include "lockable.hpp"

Lockable::Lockable() : locked_(false) {}

void Lockable::lock(ID_t e) {
    locker_ = e;
    locked_ = true;
}

void Lockable::unlock() {
    locked_ = false;
}

ID_t Lockable::getLocker() const {
    return locker_;
}

bool Lockable::isLocked() const {
    return locked_;
}
