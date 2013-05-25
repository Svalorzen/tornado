#include <SFML/Graphics.hpp>

#include <entities/people/person.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Project Tornado");

    Person p(1,1,true);

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

        window.draw(p);

        window.display();
    }

    return 0;
}
