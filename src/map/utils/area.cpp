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
    
    centroid_ = {0.0f,0.0f};
    unsigned counter = 0;
    // Computing centroid
    // Here we need the counters to be integers because we have to invert them
    // Unfortunately -(unsigned) is a huge positive number, so we need int
    for ( int i = 0; i < static_cast<int>(getMaxH()); i++ )
        for ( int j = 0; j < static_cast<int>(getMaxW()); j++ )
            if ( area_[i][j] ) {
                counter++;
                centroid_ += Distance<float>(j, -i);
            }
    
    if ( counter == 0 )
        throw std::invalid_argument("This area is empty!\n");

    // Find actual centroid
    centroid_ /= static_cast<float>(counter);
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


std::vector<Position<int>> Area::applyArea(const Position<int> & p) const {
    std::vector<Position<int>> positions;

    for ( unsigned i = 0; i < getMaxH(); i++ )
        for ( unsigned j = 0; j < getMaxW(); j++ )
            if ( area_[i][j] )
                positions.push_back(p + Distance<int>(j, -i));

    return positions;
}

// OPERATORS
Area& Area::operator+=(const Area& rhs) {
    for ( size_t i = 0; i < area_.size(); i++ )
        area_[i] |= rhs.area_[i];

    maxW_ = maxW_ > rhs.maxW_ ? maxW_ : rhs.maxW_ ;
    maxH_ = maxH_ > rhs.maxH_ ? maxH_ : rhs.maxH_ ;

    return *this;
}
Area operator+(Area lhs, const Area& rhs) {
    lhs += rhs;
    return lhs;
}

Area& Area::operator-=(const Area& rhs) {
    for ( size_t i = 0; i < area_.size(); i++ )
        area_[i] ^= ( area_[i] & rhs.area_[i] );

    normalize();

    return *this;
}
Area operator-(Area lhs, const Area& rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename T>
T reverseBitmap(T v) {
    auto r = v;

    size_t s = v.size() - 1;
    for (v >>= 1; v.any(); v >>= 1) {   
        r <<= 1;
        r[0] = v[0];
        s--;
    }
    r <<= s; // shift when v's highest bits are zero
    
    return r;
}

const Distance<float> & Area::getCentroid() const {
    return centroid_;
}
