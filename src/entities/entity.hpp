#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <graphics/animated_sprite.hpp>

#include <map/utils/position.hpp>
#include <map/utils/area.hpp>

class Map;

class Entity : public AnimatedSprite {
    public:
        Entity(Map &, Area a, bool solid); 
        Entity(Map &, Area a, bool solid, const sf::Texture & t);
        Entity(Map &, Area a, bool solid, const sf::Texture & t, const sf::IntRect & r);

        Position getPosition() const;
        Area getArea() const;

        void refresh();
        void graphicalUpdate(unsigned);

        virtual void stepUpdate() = 0;

        bool isSolid() const;
        const Map& getOwnMap() const;
    protected:

    private:
        const Map & ownMap_;

        Position position_;
        // To update the sprite we would normally store an old position and the position, and find out
        // what the difference is and render appropriately. Since the difference doesn't change during
        // a step, and we would have to compute it every time nontheless, we directly store the difference.
        Position diffPosition_;
        Area area_;

        // Represents if pathing can or can't use tiles where this entity stands. Alive stuff generally isn't solid
        // but is specially handled by the map
        bool solid_;

        void setPosition(Position);

        friend class Map;
};

#endif
