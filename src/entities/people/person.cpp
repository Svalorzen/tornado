#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

Person::Person(Map& m, int x, int y, bool isMale) : 
    Entity(m, std::make_tuple(x,y,1,1), Graphics::getTexture("src/resources/red.png")), male_(isMale) {}

void Person::goLeft() {
    Entity::Position p = getPosition();
    std::get<Entity::X>(p) += 1;

    setPosition(p);
}

void Person::goDown() {
    Entity::Position p = getPosition();
    std::get<Entity::Y>(p) += 1;

    setPosition(p);
}

void Person::goRight() {
    Entity::Position p = getPosition();
    std::get<Entity::X>(p) -= 1;

    setPosition(p);
    
}
void Person::goUp() {
    Entity::Position p = getPosition();
    std::get<Entity::Y>(p) -= 1;

    setPosition(p);
}

void Person::act() {
    static int x = 0, y = 0;

    if ( x != 2 && y == 0 ) {
        goLeft(); x++;
    }
    else if ( x == 2 && y != 2 ) {
        goDown(); y++;
    }
    else if ( y == 2 && x != 0 ) {
        goRight(); x--;
    }
    else { goUp(); y--; }

}
