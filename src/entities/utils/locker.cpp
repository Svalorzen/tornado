#include "locker.hpp"

Locker::Locker() : locking_(false) {}

void Locker::lock(ID_t e) {
    locked_ = e;
    locking_ = true;
}
void Locker::unlock() {
    locking_ = false;
}

ID_t Locker::getLocked() const {
    return locked_;
}

bool Locker::isLocking() const {
    return locking_;
}
