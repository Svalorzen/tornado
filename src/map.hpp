#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>

#include "tile.hpp"

class Map {
    public:
        Map(int,int,Tile);

    private:
        std::vector<std::vector<Tile>> grid;

};

#endif
