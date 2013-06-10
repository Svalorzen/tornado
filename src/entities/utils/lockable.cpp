#include "lockable.hpp"

Lockable::Lockable() : locked_(false) {}

void Lockable::lock(EntityBox e) {
    if ( e != nullptr ) {
        locker_ = e;
        locked_ = true;
    }
}

void Lockable::unlock() {
    locker_ = EntityBox();
    locked_ = false;
}

EntityBox & Lockable::getLocker() {
    return locker_;
}
const EntityBox & Lockable::getLocker() const {
    return locker_;
}

bool Lockable::isLocked() const {
    return locked_;
}
