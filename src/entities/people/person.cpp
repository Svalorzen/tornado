#include "person.hpp"

#include <graphics/textures.hpp>
#include <map/map.hpp>

#include <actions/action.hpp>

Person::Person(Map& m, bool isMale) : 
    //    MAP, AREA, SOLID
    Entity(m, {"1"}, false, Graphics::getTexture("src/resources/red.png")), male_(isMale) {}

Action Person::getAction() {
    static int x = 0, y = 0;
    if ( getPosition().getX() == x && getPosition().getY() == y ) {
        x = (x+6) %10;
        y = (y+13) % 10;
    }
    return Action(*this, ActionType::MOVE_TO, {x,y});
}
