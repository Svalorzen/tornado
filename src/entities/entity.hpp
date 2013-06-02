#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <graphics/animated_sprite.hpp>

#include <map/utils/position.hpp>
#include <map/utils/area.hpp>

class Map;

class Entity : public AnimatedSprite {
    public:
        Entity(Map &, Area a); 
        Entity(Map &, Area a, const sf::Texture & t);
        Entity(Map &, Area a, const sf::Texture & t, const sf::IntRect & r);

        Position getPosition() const;
        Area getArea() const;

        void refresh();
        void update(unsigned);
    protected:

    private:
        Map & ownMap_;

        Position position_;
        // To update the sprite we would normally store an old position and the position, and find out
        // what the difference is and render appropriately. Since the difference doesn't change during
        // a step, and we would have to compute it every time nontheless, we directly store the difference.
        Position diffPosition_;
        Area area_;

        void setPosition(Position);

        friend class Map;
};

#endif
