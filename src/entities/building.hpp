#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>

class Area;

class Building : public Entity {
    public:
        Building(Area);
        virtual void stepUpdate();
};

#endif
