#ifndef TILE_HEADER_FILE
#define TILE_HEADER_FILE

#include <SFML/Graphics.hpp>

class Tile:public sf::Sprite {

    public:
        Tile();

        void setEmpty(bool);
        bool getEmpty();

    private:
        bool empty;

};

#endif
