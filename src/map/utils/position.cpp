#include "position.hpp"

Position::Position() : x_(0), y_(0) {}

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
