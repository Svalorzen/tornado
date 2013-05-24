#ifndef ENTITY_HEADER_FILE
#define ENTITY_HEADER_FILE

#include <SFML/Graphics.cpp>

// X,Y,W,H
typedef std::tuple<int,int,int,int> Position;

class Entity : public sf:Sprite {
    public:
        Entity(Position); 
    private:
        enum PositionIndexes {
            X = 0,
            Y = 1,
            W = 2,
            H = 3
        };
        Position position;
};

#endif
