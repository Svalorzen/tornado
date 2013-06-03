#ifndef POSITION_HEADER_FILE
#define POSITION_HEADER_FILE

#include <utils/hashing.hpp>
#include <iostream>

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

        void print() const { std::cout << "Position## X: " << getX() << " - Y: " << getY() << "\n"; }

        void setX(int);
        void setY(int);

        Position& operator+=(const Position&);
        Position& operator-=(const Position&);

    private:
        int x_;
        int y_;
};

inline bool operator==(const Position & lhs, const Position& rhs ) {
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}

inline Position& Position::operator+=(const Position & rhs) {
    setX(getX()+rhs.getX());
    setY(getY()+rhs.getY());

    return *this;
}
inline Position operator+(Position lhs, const Position & rhs) {
    lhs += rhs;
    return lhs;
}

inline Position& Position::operator-=(const Position & rhs) {
    setX(getX()-rhs.getX());
    setY(getY()-rhs.getY());

    return *this;
}
inline Position operator-(Position lhs, const Position & rhs) {
    lhs -= rhs;
    return lhs;
}

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
