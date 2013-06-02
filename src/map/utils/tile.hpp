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

        void addEntity(Entity *);
        void rmEntity(Entity *);

        std::vector<Entity*> getEntities();

    private:
        bool walkable_;
        std::vector<Entity*> aboveEntities_;
};

#endif
