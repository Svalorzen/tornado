#ifndef THINKABLE_HEADER_FILE
#define THINKABLE_HEADER_FILE

#include <entities/entity.hpp>

class Action;

class Thinkable : public Entity {
    public:
        using Entity::Entity;

        virtual Action getAction() = 0;
};

#endif
