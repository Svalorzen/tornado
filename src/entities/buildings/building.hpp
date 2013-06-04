#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>
#include <map/utils/position.hpp>
#include <map/utils/area.hpp>

class Map;

class Building : public Entity {
    public:
        Building(const Map &,Area);
        virtual void stepUpdate();
    private:

};

#endif
