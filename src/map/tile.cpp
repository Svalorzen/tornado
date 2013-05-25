#include "tile.hpp"

Tile::Tile() : AnimatedSprite() , empty(true) {}
Tile::Tile(const sf::Texture & t) : AnimatedSprite(t), empty(true) {}
Tile::Tile(const sf::Texture & t, const sf::IntRect & r) : AnimatedSprite(t,r), empty(true) {}

void Tile::setEmpty(bool e) {
    empty = e;
}

bool Tile::getEmpty() {
    return empty;
}
