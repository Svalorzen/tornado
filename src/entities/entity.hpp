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

    protected:
        // Absolute
        void setPosition(Position);
    private:
        // X,Y,W,H
        Position position;
};

#endif
