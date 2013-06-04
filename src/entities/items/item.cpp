#include "item.hpp"

#include <graphics/textures.hpp>

Item::Item(const Map & m, ItemType t) : Entity(m, {"1"}, false, Graphics::getTexture("src/resources/yellow.png")), type_(t) {} 

ItemType Item::getType() const {
    return type_;
}

bool Item::isLocked() const {
    return locked_;
}

void Item::setLocked(bool b) {
    locked_ = b;
}

void Item::stepUpdate() {

}
