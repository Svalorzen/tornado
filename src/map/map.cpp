#include <SFML/Graphics.hpp>
#include <iostream>

#include <graphics/globals.hpp>

#include "map.hpp"

Map::Map(int x, int y) {
    sf::Texture texture;
    if ( !texture.loadFromFile("src/resource/green.png") ) std::cout << "FAILED TO LOAD TEXTURE!" << std::endl; 
    
    textures.push_back(texture);

    std::vector<Tile> dummy;
    dummy.reserve(x);
    grid.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(textures[0]);
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



