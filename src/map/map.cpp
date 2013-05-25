#include <SFML/Graphics.hpp>
#include <iostream>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include "map.hpp"

Map::Map(int x, int y) {
    // getTexture MAY THROW! 
    const sf::Texture & texture = Graphics::getTexture("src/resources/green.png");

    std::vector<Tile> dummy;
    // Reserve space in advance
    dummy.reserve(x);
    grid.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(texture);
            dummy.back().setPosition(j*Graphics::TILE_EDGE_SIZE, i*Graphics::TILE_EDGE_SIZE);
        }
        grid.push_back(dummy);
        dummy.clear();
    }
}

void Map::displayMap(sf::RenderWindow &window) {
   for ( auto & row : grid )
       for (auto & cell : row ) 
           window.draw(cell);
}



