#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <graphics/animated_sprite.hpp>

class Entity : public AnimatedSprite {
    public:
        typedef std::tuple<int,int,int,int> Position;
        enum PositionIndexes {
            X = 0,
            Y = 1,
            W = 2,
            H = 3
        };

        Entity(Position); 
        Entity(Position p, const sf::Texture & t);
        Entity(Position p, const sf::Texture & t, const sf::IntRect & r);

    protected:
        // Absolute
        void setPosition(Position);
        Position getPosition();
    private:
        // X,Y,W,H
        Position position_;
};

#endif
