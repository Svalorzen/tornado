#include "area.hpp"

#include <algorithm>
#include <iostream>

#include <map/utils/position.hpp>

Area::Area(std::initializer_list<std::string> init) {
    auto s = end(init)-1;
    size_t stringSize = (*s).size();

    // Cast is needed to convert from "ideal" constant to actual number
    size_t size = std::min(init.size(), (size_t)maxSize);

    for ( size_t i = 0; i < size; i++ ) {
        if ( (*s).size() != stringSize ) throw std::runtime_error("Init strings don't have all same size\n");

        std::bitset<maxSize> temp(*s);
        auto t = reverseBitmap(temp);

        t >>= (maxSize - stringSize);
        area_[i] = t;

        s--;
    }
    normalize();
}

const std::array<std::bitset<Area::maxSize>,Area::maxSize> & Area::getArea() const {
    return area_;
}

unsigned Area::getMaxW() const {
    return maxW_;
}

unsigned Area::getMaxH() const {
    return maxH_;
}

void Area::normalize() {
    bool addLine = true;
    unsigned emptyLines = 0;
    unsigned emptyColumns = maxSize;

    unsigned topFilledLine = 0;
    unsigned topFilledColumn = 0;

    for ( size_t i = 0; i < maxSize; i++ ) {
        // Vertical stuff
        if ( area_[i].none() ) {
            if ( addLine ) emptyLines++;
        }
        else {
            addLine = false;
            topFilledLine = i;
        }

        // Horizontal stuff
        unsigned c = 0;
        while ( !area_[i][c] && c < maxSize ) c++;
        emptyColumns = std::min(emptyColumns, c);

        for ( size_t j = c; j < maxSize; j++ )
            if ( area_[i][j] ) topFilledColumn = j;
    }

    if ( emptyLines ) {
        std::move(begin(area_)+emptyLines, end(area_), begin(area_));
    }

    if ( emptyColumns ) {
        for ( auto & i : area_ )
            i >>= emptyColumns;
    }

    maxH_ = topFilledLine - emptyLines + 1;
    maxW_ = topFilledColumn - emptyColumns + 1;
}


std::vector<Position> Area::applyArea(const Position & p) const {
    std::vector<Position> positions;

    for ( unsigned i = 0; i < getMaxH(); i++ )
        for ( unsigned j = 0; j < getMaxW(); j++ )
            if ( area_[i][j] )
                positions.push_back(p + Position(-i, j));

    return positions;
}
