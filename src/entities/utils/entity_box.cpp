#include "entity_box.hpp"

EntityBox::EntityBox() : entity_(nullptr), entityIndex_(0) {}
EntityBox::EntityBox(const Entity & e, size_t i) : entity_(&e), entityIndex_(i) {}

EntityBox::operator const Entity *() const {
    return entity_;
}

const Entity * EntityBox::operator->() const {
    return entity_;
}

size_t EntityBox::getEntityIndex() const {
    return entityIndex_;
}
