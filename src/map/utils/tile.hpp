#ifndef TILE_HEADER_FILE
#define TILE_HEADER_FILE

#include <vector>
#include <utility>

#include <utils/types.hpp>
#include <graphics/animated_sprite.hpp>

class Entity;

class Tile {
    public:
        Tile(AnimatedSprite spr);

        bool isWalkable() const;

        // We can't simply return the entities because
        // We need to update the walkable properties
        void addEntity(const Entity &);
        void rmEntity(const Entity &);

        const std::vector<std::pair<ID_t, bool>> & getEntities() const;

        void setOwnSprite(AnimatedSprite);
        AnimatedSprite & getOwnSprite();
        const AnimatedSprite & getOwnSprite() const;

    private:
        AnimatedSprite ownSprite_;

        bool walkable_;
        // This contains the solid property for all entities
        // THIS ASSUMES THAT ENTITIES CANNOT CHANGE SOLIDITY RUNTIME
        std::vector<std::pair<ID_t, bool>> aboveEntities_;
};

#endif
