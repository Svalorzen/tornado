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
    protected:

    private:
        Map & ownMap_;

        Position position_;
        Area area_;

        void setPosition(Position);

        friend class Map;
};

#endif
