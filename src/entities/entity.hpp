#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <graphics/animated_sprite.hpp>

class Map;

class Entity : public AnimatedSprite {
    public:
        typedef std::tuple<int,int,int,int> Position;
        enum PositionIndexes {
            X = 0,
            Y = 1,
            W = 2,
            H = 3
        };

        Entity(Map &, Position p); 
        Entity(Map &, Position p, const sf::Texture & t);
        Entity(Map &, Position p, const sf::Texture & t, const sf::IntRect & r);

    protected:
        // Absolute
        void setPosition(Position);
        Position getPosition();

        // Possibly methods for setting animations, used by children
    private:
        Map & ownMap_;
        // X,Y,W,H
        Position position_;
};

#endif
