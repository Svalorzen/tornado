#ifndef TILE_HEADER_FILE
#define TILE_HEADER_FILE

#include <vector>
#include <utility>

#include <utils/types.hpp>
#include <graphics/animated_sprite.hpp>

class Entity;
class AoE;

class Tile {
    public:
        Tile(AnimatedSprite spr);

        bool isWalkable() const;
        bool isBuildable() const;
        bool isShelter() const;

        // We can't simply return the entities because
        // We need to update the walkable properties
        void addEntity(const Entity &);
        void rmEntity(const Entity &);
        // These read more properties ( bad but we have no time atm )
        void addAoE(const AoE &);
        void rmAoE(const AoE &);

        const std::vector<std::pair<ID_t, bool>> & getEntities() const;

        void setOwnSprite(AnimatedSprite);
        AnimatedSprite & getOwnSprite();
        const AnimatedSprite & getOwnSprite() const;

    private:
        AnimatedSprite ownSprite_;

        bool walkable_;
        bool buildable_;
        bool shelter_;
        // This contains the solid property for all entities
        // THIS ASSUMES THAT ENTITIES CANNOT CHANGE SOLIDITY RUNTIME
        // THIS SOLUTION IS SHIT
        std::vector<std::pair<ID_t, bool>> aboveEntities_;
        std::vector<std::tuple<ID_t, bool, bool>> aboveAoEs_;
};

#endif
