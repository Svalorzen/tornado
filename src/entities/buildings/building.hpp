#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>

class Map;

class Building : public Entity {
    public:
        Building(Map&,Position);
    private:

};

#endif
