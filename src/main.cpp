#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include <globals.hpp>
#include <graphics/globals.hpp>
#include <graphics/textures.hpp>
#include <map/map.hpp>
#include <engine/game_engine.hpp>
#include <iostream>
#include <cmath>

using std::vector;

void splashScreen(sf::RenderWindow & window) {
    sf::Sprite splash(Graphics::getTexture("src/resources/splash_screen.png", false));
    splash.setPosition(10, 10);
    window.draw(splash);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        // Event reading
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
            // Spawning stuff
            else if ( event.type == sf::Event::MouseButtonPressed ||
                    ( event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::LAlt &&
                                                             event.key.code != sf::Keyboard::RAlt ))
                return;
        }
    }
}

int main() {
    Map map(100,100);
    GameEngine engine(map);

    ItemType currentItemType = ItemType::FOOD;

    sf::Sprite woodIcon(Graphics::getTexture("src/resources/wood_gui.png"));
    sf::Sprite foodIcon(Graphics::getTexture("src/resources/food_gui.png"));
    sf::Sprite selIcon(Graphics::getTexture("src/resources/selection_gui.png"));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Eat Meat and Build!", sf::Style::Titlebar);
    window.setFramerateLimit(Graphics::FPS);

    sf::Font scoreFont;
    if ( !scoreFont.loadFromFile("fonts/airstrip.ttf") ) {
        std::cout << "Could not load font.\n";
        return -1;
    }

    unsigned long score = 0;
    sf::Text scoreText("Score: "+std::to_string(score), scoreFont);

    sf::View view = window.getDefaultView();

    foodIcon.setPosition(window.mapPixelToCoords({ 10 , static_cast<int>(window.getSize().y) - 10 - 22 - 10 - 86 }));
    woodIcon.setPosition(window.mapPixelToCoords({ 10 + 95 + 10 , static_cast<int>(window.getSize().y) - 10 - 22 - 10 - 86 }));
    selIcon.setPosition(window.mapPixelToCoords({ 10 , static_cast<int>(window.getSize().y) - 10 - 22 }));

    int zoom = 0;
    float movement = 15;

    // Using chrono instead of SF::Time.. not a problem for now
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now() - std::chrono::duration<int>(1);
    unsigned oldDiff = 0;

    bool updatedView = false;
    bool changedSel = false;

    // This will be automatically limited to Graphics::FPS by SFML (setted frame rate above) 
    window.clear();
    // The idea here is that elapsed is a number [0,MS_PER_UPDATE), that represents how far we are in this frame.
    map.displayMap(window, 0);
    
    window.draw(foodIcon);
    window.draw(woodIcon);
    window.draw(selIcon);
    window.draw(scoreText);

    window.display();

    splashScreen(window);

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
                Position<int> gridPos({static_cast<int>(realCoords.x/Graphics::TILE_EDGE_SIZE),
                        static_cast<int>(realCoords.y/Graphics::TILE_EDGE_SIZE)});

                auto & grid = map.getGrid();
                try {
                    if ( grid.at(gridPos.getY()).at(gridPos.getX()).isWalkable() ) 
                        map.addItem(gridPos, currentItemType);
                } catch ( std::out_of_range ) {
                    std::cout << "I don't like you.\n";    
                }
            }
        }
        // Select Resource Type
        // Select Food
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            currentItemType = ItemType::FOOD;
            changedSel = true;
        }
        // Select Wood
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            currentItemType = ItemType::WOOD;
            changedSel = true;
        }
        // View zooming/moving
        // Zoom back
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.zoom(1.1f);
            woodIcon.setScale(woodIcon.getScale()*1.1f);
            foodIcon.setScale(foodIcon.getScale()*1.1f);
            selIcon.setScale(selIcon.getScale()*1.1f);
            scoreText.setScale(scoreText.getScale()*1.1f);
            window.setView(view);
            zoom--;
            
            movement = 15*pow(3,-tanh(zoom/2.));

            updatedView = true;
        }
        // Zoom in
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.zoom(0.909f);
            woodIcon.setScale(woodIcon.getScale()*0.909f);
            foodIcon.setScale(foodIcon.getScale()*0.909f);
            selIcon.setScale(selIcon.getScale()*0.909f);
            scoreText.setScale(scoreText.getScale()*0.909f);
            window.setView(view);
            zoom++;
            
            movement = 15*pow(3,-tanh(zoom/2.));

            updatedView = true;
        }
        // Up
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W )) {
            view.move(0,-movement);
            window.setView(view);

            updatedView = true;
        }
        // Left
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A )) {
            view.move(-movement,0);
            window.setView(view);

            updatedView = true;
        }
        // Down
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S )) {
            view.move(0,movement);
            window.setView(view);

            updatedView = true;
        }
        // Right
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D )) {
            view.move(movement,0);
            window.setView(view);

            updatedView = true;
        }

        if ( updatedView ) {
            scoreText.setPosition(window.mapPixelToCoords( {0,0} ));
            foodIcon.setPosition(window.mapPixelToCoords({ 10 , static_cast<int>(window.getSize().y) - 10 - 22 - 10 - 86 }));
            woodIcon.setPosition(window.mapPixelToCoords({ 10 + 95 + 10 , static_cast<int>(window.getSize().y) - 10 - 22 - 10 - 86 }));
        }
        
        if ( updatedView || changedSel ) {
            if ( currentItemType == ItemType::FOOD )
                selIcon.setPosition(window.mapPixelToCoords({ 10 , static_cast<int>(window.getSize().y) - 10 - 22 }));
            else if ( currentItemType == ItemType::WOOD )
                selIcon.setPosition(window.mapPixelToCoords({ 10 + 95 + 10, static_cast<int>(window.getSize().y) - 10 - 22 }));
        }

        updatedView = false;
        changedSel = false;

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
        
        window.draw(foodIcon);
        window.draw(woodIcon);
        window.draw(selIcon);
        window.draw(scoreText);

        window.display();

    }

    return 0;
}
