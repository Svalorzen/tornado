#include "tile.hpp"

Tile::Tile(){
    setEmpty(true);
    setColor(sf::Color::Green);
}

void Tile::setEmpty(bool e) {
    empty = e;
}

bool Tile::getEmpty() {
    return empty;
}
