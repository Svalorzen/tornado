#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>

#include <map/utils/tile.hpp>
#include <entities/thinkables/people/person.hpp>
#include <entities/buildings/building.hpp>

namespace sf { class Texture; class RenderWindow; }

class Map {
    public:
        Map(int,int);
        
        void runStep();
        void displayMap(sf::RenderWindow &, unsigned);

        void getPeopleActions(); //CHECK THE NEEDS OF EVERY ENTITY ON THE MAP -> COMPUTE RESULTING ACTIONS


    private:
        std::vector<std::vector<Tile>> grid_;

        std::vector<Person> people_;
        std::vector<Building> buildings_;
};

#endif
