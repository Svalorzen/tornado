#include "item.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Item::Item(ItemType t) :
    Entity({"1"}, false, AnimatedSprite(Graphics::getTexture("src/resources/yellow.png"))),
    type_(t) {} 

void Item::setType(ItemType t) {
    type_ = t;
}

ItemType Item::getType() const {
    return type_;
}

void Item::stepUpdate() {

}
