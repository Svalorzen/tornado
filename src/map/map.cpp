#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

Map::Map(int x, int y) {
    // getTexture MAY THROW! 
    const sf::Texture & texture = Graphics::getTexture("src/resources/green.png");

    std::vector<Tile> dummy;
    // Reserve space in advance
    dummy.reserve(x);
    grid_.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(texture);
            dummy.back().setPosition(j*Graphics::TILE_EDGE_SIZE, i*Graphics::TILE_EDGE_SIZE);
        }
        grid_.push_back(dummy);
        dummy.clear();
    }

    people_.emplace_back(*this, 1, 1, true);    
}

void Map::runStep() { 
    for ( auto & p : people_ )
        p.act();

}

void Map::displayMap(sf::RenderWindow &window) const {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell);
    
    for ( auto & b : buildings_ )
        window.draw(b);

    for ( auto & p : people_ )
        window.draw(p);
}

