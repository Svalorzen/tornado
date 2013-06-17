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

        std::vector<Position<int>> Astar(const Position<int> & from, const Position<int> & to);
        
    private:
        Map & ownMap_;

        Position<int> computeSingleMove(const Entity &, Position<int>); 

        // PATHING CACHE
        static constexpr unsigned MAX_PATH_CACHE = 1000;
        // This map links a pair <Entity*,Position<int>> with our last known pathfinding for it.
        // In addition, there is an iterator to the list containing the history, so that if
        // the cache is full we can remove the most old entries.
        std::unordered_map<std::pair<const Entity*, Position<int>>,
                           std::pair<std::vector<Position<int>>,
                                     std::list<std::pair<const Entity*,Position<int>>>::iterator>> cachedPaths_;
        std::list<std::pair<const Entity*,Position<int>>> cachedPathsHistory_;
};

#endif
