#include "area.hpp"

#include <algorithm>
#include <iostream>

Area::Area(std::initializer_list<std::string> init) {
    auto s = end(init)-1;
    size_t stringSize = (*s).size();

    // Cast is needed to convert from "ideal" constant to actual number
    size_t size = std::min(init.size(), (size_t)maxSize);

    for ( size_t i = 0; i < size; i++ ) {
        if ( (*s).size() != stringSize ) throw std::runtime_error("Init strings don't have all same size\n");

        std::cout << "Adding " << *s << "\n";

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

int Area::getMaxW() const {
    return maxW_;
}

int Area::getMaxH() const {
    return maxH_;
}

void Area::normalize() {
    bool addLine = true;
    unsigned emptyLines = 0;
    unsigned emptyColumns = maxSize;

    for ( size_t i = 0; i < maxSize; i++ ) {
        // Vertical stuff
        if ( addLine && area_[i].none() ) emptyLines++;
        else addLine = false;

        // Horizontal stuff
        unsigned c = 0;
        while ( !area_[i][c] && c < maxSize ) c++;
        emptyColumns = std::min(emptyColumns, c);
    }

    if ( emptyLines ) {
        std::cout << "There are empty lines: "<<emptyLines<<"\n";
        std::move(begin(area_)+emptyLines, end(area_), begin(area_));
    }

    if ( emptyColumns ) {
        std::cout << "There are empty columns: "<<emptyColumns<<"\n";
        for ( auto & i : area_ )
            i >>= emptyColumns;
    }
}
