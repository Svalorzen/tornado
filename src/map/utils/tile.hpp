#ifndef TILE_HEADER_FILE
#define TILE_HEADER_FILE

#include <vector>
#include <graphics/animated_sprite.hpp>

class Entity;

class Tile : public AnimatedSprite {
    public:
        Tile();
        Tile(const sf::Texture &);
        Tile(const sf::Texture &, const sf::IntRect &);

        bool isWalkable() const;

        void addEntity(const Entity *);
        void rmEntity(const Entity *);

        std::vector<const Entity*> getEntities();

    private:
        bool walkable_;
        std::vector<const Entity*> aboveEntities_;
};

#endif
