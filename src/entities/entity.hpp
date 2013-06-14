#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <utils/types.hpp>

#include <graphics/animated_sprite.hpp>

#include <map/utils/position.hpp>
#include <map/utils/distance.hpp>
#include <map/utils/area.hpp>

class Entity {
    public:
        Entity(const Area &, bool, const AnimatedSprite &); 
        Entity(const Position<int> &, const Area &, bool, const AnimatedSprite &);

        void setPosition(const Position<int> &);
        const Position<int> & getPosition() const;

        const Distance<int> & getStepDiff() const;

        void setArea(const Area&);
        const Area & getArea() const;

        void setSolid(bool);
        bool isSolid() const;

        void setOwnSprite(const AnimatedSprite&);
        AnimatedSprite & getOwnSprite();
        const AnimatedSprite & getOwnSprite() const;

        virtual void stepUpdate() = 0;

        void refresh();
        void graphicalUpdate(unsigned msLapsed);

        ID_t getId() const;

        std::vector<ID_t> & getInventory();
        const std::vector<ID_t> & getInventory() const;

    private:
        int id_;
        Position<int> position_;
        Area area_;
        // To update the sprite we would normally store an old position and the position, and find out
        // what the difference is and render appropriately. Since the difference doesn't change during
        // a step, and we would have to compute it every time nontheless, we directly store the difference.
        Distance<int> stepDiff_;

        // Represents if pathing can or can't use tiles where this entity stands. Alive stuff generally isn't solid
        // but is specially handled by the map
        bool solid_;

        AnimatedSprite ownSprite_;

        // INVENTORY - need functions to get/remove objects
        std::vector<ID_t> inventory_;

        static ID_t idCreator_;
};

#endif
