#include "distance.hpp"

#include <cstdlib>

#include <map/utils/position.hpp>

Distance::Distance(int dx, int dy) : diffX_(dx), diffY_(dy) {}
Distance::Distance() : Distance(0,0) {} 

unsigned Distance::getDiffXu() const {
    return abs(diffX_); 
}
unsigned Distance::getDiffYu() const {
    return abs(diffY_);
}

int Distance::getDiffXi() const {
    return diffX_;
}
int Distance::getDiffYi() const {
    return diffY_;
}

unsigned Distance::getDistance() const {
    return abs(diffX_) + abs(diffY_);
}

void Distance::setDiffX(int dx) {
    diffX_ = dx;
}
void Distance::setDiffY(int dy) {
    diffY_ = dy;
}

Distance& Distance::operator+=(const Distance& rhs) {
    diffX_ += rhs.diffX_;
    diffY_ += rhs.diffY_;

    return *this;
}
Distance& Distance::operator-=(const Distance& rhs) {
    diffX_ -= rhs.diffX_;
    diffY_ -= rhs.diffY_;

    return *this;
}
Distance& Distance::operator/=(float rhs) {
    diffX_ /= rhs;
    diffY_ /= rhs;

    return *this;
}
Distance& Distance::operator*=(float rhs) {
    diffX_ *= rhs;
    diffY_ *= rhs;

    return *this;
}

bool operator==(const Distance& lhs, const Distance& rhs) {
    return lhs.getDistance() == rhs.getDistance();
}
bool operator!=(const Distance& lhs, const Distance& rhs) {
    return !operator==(lhs, rhs);
}

bool operator<(const Distance& lhs, const Distance& rhs) {
    return lhs.getDistance() < rhs.getDistance();
}
bool operator<=(const Distance& lhs, const Distance& rhs) {
    return !operator>(lhs,rhs);
}

bool operator>(const Distance& lhs, const Distance& rhs) {
    return operator<(rhs,lhs);
}
bool operator>=(const Distance& lhs, const Distance& rhs) {
    return !operator<(lhs,rhs);
}

Distance operator+(Distance lhs, const Distance& rhs) {
    lhs += rhs;
    return lhs;
}
Distance operator-(Distance lhs, const Distance& rhs) {
    lhs -= rhs;
    return lhs;
}
Distance operator-(Distance lhs) {
    lhs.setDiffX(-lhs.getDiffXi());
    lhs.setDiffY(-lhs.getDiffYi());

    return lhs;
}

Distance operator*(Distance lhs, float rhs) {
    lhs *= rhs;
    return lhs;
}
Distance operator*(float lhs, Distance rhs) {
    return operator*(rhs,lhs);
}

Distance operator/(Distance lhs, float rhs) {
    lhs /= rhs;
    return lhs;
}
Distance operator/(float lhs, Distance rhs) {
    return operator/(rhs,lhs);
}
