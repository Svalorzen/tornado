#include <SFML/Graphics.hpp>

#include "map/map.hpp"

int main()
{
    Map myMap(10,10);
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        myMap.displayMap(window);
        window.display();
    }

    return 0;

}
