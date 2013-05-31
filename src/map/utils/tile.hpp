#ifndef TILE_HEADER_FILE
#define TILE_HEADER_FILE

#include <graphics/animated_sprite.hpp>

class Tile : public AnimatedSprite {

    public:
        Tile();
        Tile(const sf::Texture &);
        Tile(const sf::Texture &, const sf::IntRect &);

        void setEmpty(bool);
        bool getEmpty();

    private:
        bool empty;

};

#endif
