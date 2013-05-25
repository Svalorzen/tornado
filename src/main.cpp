#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include <entities/people/person.hpp>
#include <map/map.hpp>
#include <iostream>

using std::vector;

int main() {
    Map myMap(10,10);

    vector<Person> villagers;
    villagers.emplace_back(1,1,true);
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");

    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
        }

        // We will need to do work during frames, can't do it all at once..
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        int diff = std::chrono::duration_cast<std::chrono::seconds>(t2 - t).count();

        if ( diff ) {
            for ( auto & v : villagers )
                v.act();

            // Reset timer for next seconds
            // FIXME: THIS IS WRONG BECAUSE ERRORS ACCUMULATE
            t = t2;
        }


        window.clear();

        myMap.displayMap(window);
        window.draw(villagers[0]);

        window.display();
    }

    return 0;

}
