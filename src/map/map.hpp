#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>
#include <unordered_map>
#include <utility>
#include <list>

#include <map/utils/tile.hpp>
#include <map/utils/position.hpp>
#include <entities/people/person.hpp>
#include <entities/buildings/building.hpp>

namespace sf { class Texture; class RenderWindow; }

//class Entity;
#include <entities/entity.hpp>

class Map {
    public:
        Map(int,int);
        
        void runStep();
        void displayMap(sf::RenderWindow &, unsigned);

    private:
        std::vector<std::vector<Tile>> grid_;

        std::vector<Person> people_;
        std::vector<Building> buildings_;

        Position computeSingleMove(const Entity &, Position); 

        // This map links a pair <Entity*,Position> with our last known pathfinding for it.
        // In addition, there is an iterator to the list containing the history, so that if
        // the cache is full we can remove the most old entries.
        std::unordered_map<std::pair<const Entity*, Position>,
                std::pair<std::vector<Position>,
                          std::list<std::pair<const Entity*,Position> >::iterator> > cachedPaths_;
        std::list<std::pair<const Entity*,Position>> cachedPathsHistory_;
        static constexpr unsigned MAX_PATH_CACHE = 1000;
};

#endif
