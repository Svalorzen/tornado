#ifndef AOE_HEADER_FILE
#define AOE_HEADER_FILE

#include <entities/entity.hpp>

class Area;

class AoE : public Entity {
    public:
        AoE(Area);

        bool isBuildable() const;
        bool isShelter() const;

        void setBuildable(bool);
        void setShelter(bool);

        void stepUpdate();
    private:
        bool buildable_;
        bool shelter_;
};

#endif
