#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>

#include <map/tile.hpp>
#include <entities/people/person.hpp>
#include <entities/buildings/building.hpp>

namespace sf { class Texture; class RenderWindow; }

class Map {
    public:
        Map(int,int);
        
        void runStep();
        void displayMap(sf::RenderWindow &) const;

    private:
        std::vector<std::vector<Tile>> grid_;

        std::vector<Person> people_;
        std::vector<Building> buildings_;
};

#endif
