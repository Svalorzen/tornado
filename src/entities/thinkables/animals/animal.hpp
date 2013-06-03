#ifndef ANIMAL_HEADER_FILE
#define ANIMAL_HEADER_FILE

#include <entities/thinkables/thinkable.hpp>
#include <actions/action.hpp>

class Map;

class Animal : public Thinkable {
    public:
        Animal(Map&);
};

#endif
