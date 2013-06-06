#include "position.hpp"

#include <map/utils/distance.hpp>

Position::Position(int x, int y) : x_(x), y_(y) {}
Position::Position() : Position(0,0) {}

int Position::getX() const {
    return x_;
}

int Position::getY() const {
    return y_;
}

void Position::setX(int newX) {
    x_ = newX;
}

void Position::setY(int newY) {
    y_ = newY;
}

// ORIGIN IS TOP LEFT
Position Position::up() const {
   Position p = *this;
   p.setY(getY() - 1);
   return p;
}

Position Position::down() const {
   Position p = *this;
   p.setY(getY() + 1);
   return p;
}

Position Position::left() const {
   Position p = *this;
   p.setX(getX() - 1);
   return p;
}

Position Position::right() const {
   Position p = *this;
   p.setX(getX() + 1);
   return p;
}

// EQUALITY
bool operator==(const Position & lhs, const Position& rhs ) {
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}
bool operator!=(const Position & lhs, const Position& rhs ) {
    return !operator==(lhs,rhs);
}

// PLUS STUFF
Position& Position::operator+=(const Distance & rhs) {
    setX(getX()+rhs.getDiffXi());
    setY(getY()+rhs.getDiffYi());

    return *this;
}

Position operator+(Position lhs, const Distance & rhs) {
    lhs += rhs;
    return lhs;
}
Position operator+(const Distance& lhs, const Position & rhs) {
    return operator+(rhs,lhs);
}

// MINUS STUFF
Position& Position::operator-=(const Distance & rhs) {
    setX(getX()-rhs.getDiffXi());
    setY(getY()-rhs.getDiffYi());

    return *this;
}

Position operator-(Position lhs, const Distance & rhs) {
    lhs -= rhs;
    return lhs;
}
Position operator-(const Distance& lhs, const Position & rhs) {
    return operator-(rhs,lhs);
}
Distance operator-(const Position& lhs, const Position & rhs) {
    return Distance(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY());
}
