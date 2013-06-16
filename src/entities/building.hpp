#ifndef BUILDING_HEADER_FILE
#define BUILDING_HEADER_FILE

#include <entities/entity.hpp>
#include <entities/utils/lockable.hpp>

enum class BuildingType {
    HOUSE
};

class Area;

class Building : public Entity, public Lockable {
    public:
        Building(Area, BuildingType);
        virtual void stepUpdate();
   
        BuildingType getType();
        bool isValid() const;

        ID_t getUnbuildableArea() const;
        void setUnbuildableArea(ID_t);

        void validate();

        bool isOwned() const;
        void disown();

        ID_t getOwner() const;
        void setOwner(ID_t);
    private:
        BuildingType type_;
        ID_t owner_;

        ID_t unbuildableArea_;

        bool valid_;
        bool owned_;
};

#endif
