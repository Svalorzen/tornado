#ifndef POSITION_HEADER_FILE
#define POSITION_HEADER_FILE

#include <utils/hashing.hpp>
#include <iostream>

class Distance;

class Position {
    public:
        Position();
        Position(int, int);

        int getX() const;
        int getY() const;

        Position up() const;
        Position down() const;
        Position left() const;
        Position right() const;

        void print() const { std::cout << "{ X: " << getX() << " , Y: " << getY() << " }"; }

        void setX(int);
        void setY(int);

        Position& operator+=(const Distance&);
        Position& operator-=(const Distance&);

    private:
        int x_;
        int y_;
};


bool operator==(const Position & lhs, const Position& rhs );
bool operator!=(const Position & lhs, const Position& rhs );

Position operator+(Position lhs, const Distance & rhs);
Position operator+(const Distance & lhs, const Position & rhs);

Position operator-(Position lhs, const Distance & rhs);
Position operator-(const Distance & lhs, const Position & rhs);
Distance operator-(const Position & lhs, const Position & rhs);

// Hashing specialization
namespace std {
    template <>
    struct hash<Position> {
        inline size_t operator()(const Position& p) const { 
            size_t seed = 0;
            Utils::hash_combine(seed, p.getX());
            Utils::hash_combine(seed, p.getY());
            return seed;
        }
    };
}

#endif
