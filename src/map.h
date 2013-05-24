#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>

#include "tile.h"

class Map {
    public:
        Map(int,int);

    private:
        std::vector<std::vector<Tile>> grid;

};

#endif
