#include "locker.hpp"

Locker::Locker() : locking_(false) {}

void Locker::lock(EntityBox e) {
    if ( e != nullptr ) {
        locked_ = e;
        locking_ = true;
    }
}
void Locker::unlock() {
    locked_ = EntityBox();
    locking_ = false;
}

EntityBox & Locker::getLocked() {
    return locked_;
}
const EntityBox & Locker::getLocked() const {
    return locked_;
}

bool Locker::isLocking() const {
    return locking_;
}
