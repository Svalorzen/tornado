#include "item.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Item::Item(ItemType t) :
    Entity({"1"}, false, AnimatedSprite(Graphics::getTexture("src/resources/yellow.png"))),
    locked_(false),
    type_(t) {} 

void Item::setType(ItemType t) {
    type_ = t;
}

ItemType Item::getType() const {
    return type_;
}

void Item::setLocked(bool b) {
    locked_ = b;
}

bool Item::isLocked() const {
    return locked_;
}

void Item::stepUpdate() {

}
