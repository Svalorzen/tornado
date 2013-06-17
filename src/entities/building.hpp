#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>
#include <entities/utils/lockable.hpp>
#include <entities/utils/ownable.hpp>

enum class BuildingType {
    HOUSE
};

class Area;

class Building : public Entity, public Lockable, public Ownable {
    public:
        Building(Area, BuildingType);
        virtual void stepUpdate();
   
        BuildingType getType();
        bool isValid() const;

        ID_t getUnbuildableArea() const;
        void setUnbuildableArea(ID_t);

        void validate();

    private:
        BuildingType type_;
        ID_t unbuildableArea_;

        bool valid_;
};

#endif
