#include <cstdlib>
#include <cmath>

#include <map/utils/position.hpp>

template <typename T>
Distance<T>::Distance(T dx, T dy) : diffX_(dx), diffY_(dy) {}
template <typename T>
Distance<T>::Distance() : Distance(0,0) {} 

template <typename T>
template <typename M>
Distance<T>::Distance(const Distance<M> & dm) : diffX_(static_cast<T>(dm.getDiffXi())),
                                                diffY_(static_cast<T>(dm.getDiffYi())) {}

template <typename T>
T Distance<T>::getDiffXu() const {
    return std::abs(diffX_); 
}
template <typename T>
T Distance<T>::getDiffYu() const {
    return std::abs(diffY_);
}

template <typename T>
T Distance<T>::getDiffXi() const {
    return diffX_;
}
template <typename T>
T Distance<T>::getDiffYi() const {
    return diffY_;
}

template <typename T>
T Distance<T>::getDistance() const {
    return std::abs(diffX_) + std::abs(diffY_);
}

template <typename T>
void Distance<T>::setDiffX(T dx) {
    diffX_ = dx;
}
template <typename T>
void Distance<T>::setDiffY(T dy) {
    diffY_ = dy;
}

template <typename T>
Distance<T>& Distance<T>::operator+=(const Distance<T>& rhs) {
    diffX_ += rhs.diffX_;
    diffY_ += rhs.diffY_;

    return *this;
}
template <typename T>
Distance<T>& Distance<T>::operator-=(const Distance<T>& rhs) {
    diffX_ -= rhs.diffX_;
    diffY_ -= rhs.diffY_;

    return *this;
}
template <typename T>
Distance<T>& Distance<T>::operator/=(float rhs) {
    diffX_ /= rhs;
    diffY_ /= rhs;

    return *this;
}
template <typename T>
Distance<T>& Distance<T>::operator*=(float rhs) {
    diffX_ *= rhs;
    diffY_ *= rhs;

    return *this;
}

template <typename T>
bool operator==(const Distance<T>& lhs, const Distance<T>& rhs) {
    return lhs.getDistance() == rhs.getDistance();
}
template <typename T>
bool operator!=(const Distance<T>& lhs, const Distance<T>& rhs) {
    return !operator==(lhs, rhs);
}

template <typename T>
bool operator<(const Distance<T>& lhs, const Distance<T>& rhs) {
    return lhs.getDistance() < rhs.getDistance();
}
template <typename T>
bool operator<=(const Distance<T>& lhs, const Distance<T>& rhs) {
    return !operator>(lhs,rhs);
}

template <typename T>
bool operator>(const Distance<T>& lhs, const Distance<T>& rhs) {
    return operator<(rhs,lhs);
}
template <typename T>
bool operator>=(const Distance<T>& lhs, const Distance<T>& rhs) {
    return !operator<(lhs,rhs);
}

template <typename T>
Distance<T> operator+(Distance<T> lhs, const Distance<T>& rhs) {
    lhs += rhs;
    return lhs;
}
template <typename T>
Distance<T> operator-(Distance<T> lhs, const Distance<T>& rhs) {
    lhs -= rhs;
    return lhs;
}
template <typename T>
Distance<T> operator-(Distance<T> lhs) {
    lhs.setDiffX(-lhs.getDiffXi());
    lhs.setDiffY(-lhs.getDiffYi());

    return lhs;
}

template <typename T>
Distance<T> operator*(Distance<T> lhs, float rhs) {
    lhs *= rhs;
    return lhs;
}
template <typename T>
Distance<T> operator*(float lhs, Distance<T> rhs) {
    return operator*(rhs,lhs);
}

template <typename T>
Distance<T> operator/(Distance<T> lhs, float rhs) {
    lhs /= rhs;
    return lhs;
}
template <typename T>
Distance<T> operator/(float lhs, Distance<T> rhs) {
    return operator/(rhs,lhs);
}
