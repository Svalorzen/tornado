#ifndef MAP_AREA_HEADER_FILE
#define MAP_AREA_HEADER_FILE

#include <initializer_list>
#include <array>
#include <vector>
#include <bitset>
#include <string>

class Position;

class Area {
    public:
        static const size_t maxSize = 8u;

        Area(std::initializer_list<std::string>); 

        const std::array<std::bitset<maxSize>,maxSize> & getArea() const;

        unsigned getMaxH() const;
        unsigned getMaxW() const;

        Area& operator+=(const Area&);
        Area& operator-=(const Area&);

        std::vector<Position> applyArea(const Position &) const;

    private:
        std::array<std::bitset<maxSize>,maxSize> area_; 
        unsigned maxH_;
        unsigned maxW_;

        void normalize();
};

Area operator+(Area lhs, const Area& rhs);
Area operator-(Area lhs, const Area& rhs);

template <typename T>
T reverseBitmap(T v);

#endif
