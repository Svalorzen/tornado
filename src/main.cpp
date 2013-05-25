#include <SFML/Graphics.hpp>

#include <entities/people/person.hpp>
#include "map/map.hpp"

int main() {
    Map myMap(10,10);
    Person p(1,1,true);
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
        }

        window.clear();

        myMap.displayMap(window);
        window.draw(p);

        window.display();
    }

    return 0;

}
