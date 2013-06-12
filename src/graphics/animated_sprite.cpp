#include "animated_sprite.hpp"

AnimatedSprite::AnimatedSprite() : Sprite() {}
AnimatedSprite::AnimatedSprite(const sf::Texture & t) : Sprite(t) {}
AnimatedSprite::AnimatedSprite(const sf::Texture & t, const sf::IntRect & r) : Sprite(t,r) {}

void AnimatedSprite::resize(int width, int height) {
    sf::FloatRect self = Sprite::getLocalBounds();
    Sprite::setScale((float)(width/self.width), (float)(height/self.height));
}

bool AnimatedSprite::getToRender() {
    return toRender_;
}

void AnimatedSprite::setToRender(bool b) {
    toRender_ = b;
}
