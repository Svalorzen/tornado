#ifndef ANIMAL_HEADER_FILE
#define ANIMAL_HEADER_FILE

#include <entities/entity.hpp>

class Animal : public Entity {
    public:
        Animal();

        virtual void stepUpdate();
};

#endif
