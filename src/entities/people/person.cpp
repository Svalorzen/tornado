#include "person.hpp"

Person::Person(int x, int y, bool isMale) : Entity(std::make_tuple(x,y,1,1)), male(isMale) {}
