#include "item.hpp"

#include <graphics/textures.hpp>
#include <graphics/animated_sprite.hpp>

Item::Item(ItemType t) :
    Entity({"1"}, false, AnimatedSprite()),
    type_(t) {

    if ( t == ItemType::FOOD )
        getOwnSprite().sf::Sprite::setTexture(Graphics::getTexture("src/resources/food.png"));
    else if ( t == ItemType::WOOD )
        getOwnSprite().sf::Sprite::setTexture(Graphics::getTexture("src/resources/wood.png"));

} 

void Item::setType(ItemType t) {
    type_ = t;
}

ItemType Item::getType() const {
    return type_;
}

void Item::stepUpdate() {

}
