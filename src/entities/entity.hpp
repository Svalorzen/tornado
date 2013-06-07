#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <graphics/animated_sprite.hpp>

#include <map/utils/position.hpp>
#include <map/utils/distance.hpp>
#include <map/utils/area.hpp>

class Entity {
    public:
        Entity(const Area &, bool, const AnimatedSprite &); 
        Entity(const Position &, const Area &, bool, const AnimatedSprite &);

        void setPosition(const Position &);
        Position getPosition() const;

        Distance getStepDiff() const;

        void setArea(const Area&);
        Area getArea() const;

        void setSolid(bool);
        bool isSolid() const;

        void setOwnSprite(const AnimatedSprite&);
        AnimatedSprite & getOwnSprite();
        const AnimatedSprite & getOwnSprite() const;

        virtual void stepUpdate() = 0;

        void refresh();
        void graphicalUpdate(unsigned msLapsed);

        int getId() const;

    private:
        int id_;
        Position position_;
        Area area_;
        // To update the sprite we would normally store an old position and the position, and find out
        // what the difference is and render appropriately. Since the difference doesn't change during
        // a step, and we would have to compute it every time nontheless, we directly store the difference.
        Distance stepDiff_;

        // Represents if pathing can or can't use tiles where this entity stands. Alive stuff generally isn't solid
        // but is specially handled by the map
        bool solid_;

        AnimatedSprite ownSprite_;

        // INVENTORY - need functions to get/remove objects
        std::vector<Entity*> inventory;

        static long long unsigned idCreator_;
};

#endif
