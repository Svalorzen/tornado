#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include <globals.hpp>
#include <graphics/globals.hpp>
#include <map/map.hpp>
#include <engine/game_engine.hpp>
#include <iostream>
#include <cmath>

using std::vector;

int main() {
    Map map(100,100);
    GameEngine engine(map);

    ItemType currentItemType = ItemType::FOOD;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tornado!");
    window.setFramerateLimit(Graphics::FPS);

    sf::Font scoreFont;
    if ( !scoreFont.loadFromFile("fonts/airstrip.ttf") ) {
        std::cout << "Could not load font.\n";
        return -1;
    }

    unsigned long score = 0;
    sf::Text scoreText("Score: "+std::to_string(score), scoreFont);

    sf::View view = window.getDefaultView();
    int zoom = 0;
    float movement = 15;

    // Using chrono instead of SF::Time.. not a problem for now
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now() - std::chrono::duration<int>(1);
    unsigned oldDiff = 0;

    while (window.isOpen()) {
        sf::Event event;
        // Event reading
        while (window.pollEvent(event)) {
            // Closing game events (Esc + clicking on the 'x' button)
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
            // Spawning stuff
            else if ( event.type == sf::Event::MouseButtonPressed ) {
                auto realCoords = window.mapPixelToCoords( {event.mouseButton.x, event.mouseButton.y} );
                map.addItem({static_cast<int>(realCoords.x/Graphics::TILE_EDGE_SIZE),
                        static_cast<int>(realCoords.y/Graphics::TILE_EDGE_SIZE)}, currentItemType);
            }
        }
        // Select Resource Type
        // Select Food
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            currentItemType = ItemType::FOOD;
        }
        // Select Wood
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            currentItemType = ItemType::WOOD;
        }
        // View zooming/moving
        // Zoom back
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.zoom(1.1f);
            window.setView(view);
            zoom--;
            
            movement = 15*pow(3,-tanh(zoom/2.));
            
            //if ( zoom < 0 )
            //    movement *= 1.5f;
            //else
            //    movement *= 1.05f;
        }
        // Zoom in
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.zoom(0.909f);
            window.setView(view);
            zoom++;
            
            movement = 15*pow(3,-tanh(zoom/2.));
            
            //if ( zoom <= 0 )
            //    movement /= 1.5f;
            //else
            //    movement /= 1.05f;
        }
        // Up
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W )) {
            view.move(0,-movement);
            window.setView(view);
        }
        // Left
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A )) {
            view.move(-movement,0);
            window.setView(view);
        }
        // Down
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S )) {
            view.move(0,movement);
            window.setView(view);
        }
        // Right
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D )) {
            view.move(movement,0);
            window.setView(view);
        }

        // We will need to do work during frames, can't do it all at once..
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        unsigned elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(t-start).count();
        unsigned diff = elapsedMs / Core::MS_PER_UPDATE;

        // Update world state once per second
        if ( diff > oldDiff ) {
            engine.runStep();
            score += map.getPeople().size();
            scoreText.setString("Score: "+std::to_string(score));

            oldDiff = diff;
            // We reset this because runStep already forces stuff to snap to the grid (moving them),
            // so in case display gets called we don't want stuff to move more
            elapsedMs = 0;
        }
        else
            // Not sure if it'll work but let's see!
            elapsedMs -= oldDiff * Core::MS_PER_UPDATE;

        // This will be automatically limited to Graphics::FPS by SFML (setted frame rate above) 
        window.clear();
        // The idea here is that elapsed is a number [0,MS_PER_UPDATE), that represents how far we are in this frame.
        map.displayMap(window, elapsedMs);
        window.draw(scoreText);

        window.display();

    }

    //Map map(10,10);
    //Person p(map, true);
    //printArea(p.getArea());
    return 0;

}
