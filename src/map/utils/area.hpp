#ifndef MAP_AREA_HEADER_FILE
#define MAP_AREA_HEADER_FILE

#include <initializer_list>
#include <array>
#include <vector>
#include <bitset>
#include <string>

#include <iostream>

class Position;
#include <map/utils/distance.hpp>

class Area {
    public:
        static const size_t maxSize = 8u;

        Area(std::initializer_list<std::string>); 

        const std::array<std::bitset<maxSize>,maxSize> & getArea() const;

        unsigned getMaxH() const;
        unsigned getMaxW() const;

        const Distance & getCentroid() const;

        Area& operator+=(const Area&);
        Area& operator-=(const Area&);

        std::vector<Position> applyArea(const Position &) const;

        void print() const {
            auto k = getArea();    

            for ( auto j = k.rbegin(); j != k.rend(); j++ ) {
                for ( size_t i = 0; i < (*j).size(); i++ )
                    std::cout << (*j)[i];
                std::cout << std::endl;
            }
        }

    private:
        std::array<std::bitset<maxSize>,maxSize> area_; 
        unsigned maxH_;
        unsigned maxW_;

        Distance centroid_;

        void normalize();
};

Area operator+(Area lhs, const Area& rhs);
Area operator-(Area lhs, const Area& rhs);

template <typename T>
T reverseBitmap(T v);

#endif
