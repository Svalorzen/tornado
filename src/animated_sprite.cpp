#include "animated_sprite.hpp"

AnimatedSprite() : Sprite() {}
AnimatedSprite(const sf::Texture & t) : Sprite(t) {}
AnimatedSprite(const sf::Texture & t, const sf::IntRect & r) : Sprite(t,r) {}
