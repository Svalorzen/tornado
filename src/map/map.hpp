#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>

#include "tile.hpp"

namespace sf { class Texture; class RenderWindow; }

class Map {
    public:
        Map(int,int);
        
        void displayMap(sf::RenderWindow &);


    private:
        std::vector<std::vector<Tile>> grid;
        std::vector<sf::Texture> textures;
        
};

#endif
