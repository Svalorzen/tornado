#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <actions/action.hpp>

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

    Person p(*this, true);
    p.setPosition({1,1});
    p.refresh();
    people_.push_back(p);    
}

void Map::runStep() { 
    std::vector<Action> actions;
    for ( auto & p : people_ ) {
        actions.push_back(p.getAction());
        // Set people so that graphically they are actually in the square they had to go previous turn,
        // so that there shouldn't be circular turns
        p.refresh();
    }

    for ( auto & a : actions ) {
        switch( a.getActionType() ) {
            case ActionType::MOVE_UP: {
                a.getEntity().setPosition(a.getEntity().getPosition().up()); 
                break;
            }
            case ActionType::MOVE_DOWN: {
                a.getEntity().setPosition(a.getEntity().getPosition().down()); 

                break;
            }
            case ActionType::MOVE_LEFT: {
                a.getEntity().setPosition(a.getEntity().getPosition().left()); 

                break;
            }
            case ActionType::MOVE_RIGHT: {
                a.getEntity().setPosition(a.getEntity().getPosition().right()); 

                break;
            }
            default: std::cout << "LOL\n" ;
        }
    }
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell);
    
    for ( auto & b : buildings_ ) {
        window.draw(b);
        b.update(elapsedMs);
    }

    for ( auto & p : people_ ) {
        window.draw(p);
        p.update(elapsedMs);
    }
}

