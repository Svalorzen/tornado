#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>

enum class BuildingType {
    HOUSE
};

class Area;

class Building : public Entity {
    public:
        Building(Area, BuildingType);
        virtual void stepUpdate();
   
        BuildingType getType();

    private:

        BuildingType type_;

};

#endif
