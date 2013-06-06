#ifndef GAME_ENGINE_HEADER_FILE
#define GAME_ENGINE_HEADER_FILE

#include <vector>
#include <unordered_map>
#include <utility>
#include <list>

#include <map/utils/position.hpp>

class Map;
class Entity;

class GameEngine {
    public:
        GameEngine(Map &);

        void runStep();

        
    private:
        Map & ownMap_;

        Position computeSingleMove(const Entity &, Position); 

        // PATHING CACHE
        static constexpr unsigned MAX_PATH_CACHE = 1000;
        // This map links a pair <Entity*,Position> with our last known pathfinding for it.
        // In addition, there is an iterator to the list containing the history, so that if
        // the cache is full we can remove the most old entries.
        std::unordered_map<std::pair<const Entity*, Position>,
                           std::pair<std::vector<Position>,
                                     std::list<std::pair<const Entity*,Position>>::iterator>> cachedPaths_;
        std::list<std::pair<const Entity*,Position>> cachedPathsHistory_;
};

#endif
