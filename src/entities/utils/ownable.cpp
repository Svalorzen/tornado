#include "ownable.hpp"

Ownable::Ownable() : owned_(false) {}

void Ownable::setOwner(ID_t e) {
    owner_ = e;
    owned_ = true;
}

void Ownable::disown() {
    owned_ = false;
}

ID_t Ownable::getOwner() const {
    return owner_;
}

bool Ownable::isOwned() const {
    return owned_;
}
