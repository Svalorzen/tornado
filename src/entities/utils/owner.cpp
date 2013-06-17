#include "owner.hpp"

Owner::Owner() : owner_(false) {}

void Owner::own(ID_t e) {
    owned_ = e;
    owner_ = true;
}
void Owner::disown() {
    owner_ = false;
}

ID_t Owner::getOwned() const {
    return owned_;
}

bool Owner::isOwner() const {
    return owner_;
}
