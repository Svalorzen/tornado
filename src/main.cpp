#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include <globals.hpp>
#include <graphics/globals.hpp>
#include <map/map.hpp>
#include <iostream>

using std::vector;

void printArea(Area a) {
    auto k = a.getArea();    

    for ( auto j = k.rbegin(); j != k.rend(); j++ ) {
        for ( size_t i = 0; i < (*j).size(); i++ )
            std::cout << (*j)[i];
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    Map myMap(10,10);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Map Test");
    window.setFramerateLimit(Graphics::FPS);

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
        }

        // We will need to do work during frames, can't do it all at once..
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        unsigned elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(t-start).count();
        unsigned diff = elapsedMs / Core::MS_PER_UPDATE;

        // Update world state once per second
        if ( diff > oldDiff ) {
            std::cout << "running\n";
            myMap.runStep();

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
        myMap.displayMap(window, elapsedMs);
        window.display();

    }

    //Map myMap(10,10);
    //Person p(myMap, true);
    //printArea(p.getArea());
    return 0;

}
