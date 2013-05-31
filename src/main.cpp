#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include <entities/people/person.hpp>
#include <map/map.hpp>
#include <iostream>

#include <map/utils/area.hpp>

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
            myMap.runStep();
            // Reset timer for next seconds
            // FIXME: THIS IS WRONG BECAUSE ERRORS ACCUMULATE
            t = t2;
        }


        window.clear();

        myMap.displayMap(window);

        window.display();
    }

    //Map myMap(10,10);
    //Person p(myMap, true);
    //printArea(p.getArea());
    return 0;

}
