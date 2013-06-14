#include <map/utils/distance.hpp>

template <typename T>
Position<T>::Position(T x, T y) : x_(x), y_(y) {}
template <typename T>
Position<T>::Position() : Position(0,0) {}

template <typename T>
template <typename M>
Position<T>::Position(const Position<M> & pm) : x_(static_cast<T>(pm.getX())),
                                                y_(static_cast<T>(pm.getY())) {}

template <typename T>
T Position<T>::getX() const {
    return x_;
}

template <typename T>
T Position<T>::getY() const {
    return y_;
}

template <typename T>
void Position<T>::setX(T newX) {
    x_ = newX;
}

template <typename T>
void Position<T>::setY(T newY) {
    y_ = newY;
}

// ORIGIN IS TOP LEFT
template <typename T>
Position<T> Position<T>::up() const {
   Position<T> p = *this;
   p.setY(getY() - 1);
   return p;
}

template <typename T>
Position<T> Position<T>::down() const {
   Position<T> p = *this;
   p.setY(getY() + 1);
   return p;
}

template <typename T>
Position<T> Position<T>::left() const {
   Position<T> p = *this;
   p.setX(getX() - 1);
   return p;
}

template <typename T>
Position<T> Position<T>::right() const {
   Position<T> p = *this;
   p.setX(getX() + 1);
   return p;
}
// ASSIGNMENT
template <typename T>
template <typename M>
Position<T>& Position<T>::operator=(const Position<M>& rhs) {
    setX(static_cast<T>(rhs.getX()));
    setY(static_cast<T>(rhs.getY()));

    return *this;
}
// EQUALITY
template <typename T>
bool operator==(const Position<T> & lhs, const Position<T>& rhs ) {
    return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
}
template <typename T>
bool operator!=(const Position<T> & lhs, const Position<T>& rhs ) {
    return !operator==(lhs,rhs);
}

// PLUS STUFF
template <typename T>
Position<T>& Position<T>::operator+=(const Distance<T> & rhs) {
    setX(getX()+rhs.getDiffXi());
    setY(getY()+rhs.getDiffYi());

    return *this;
}

template <typename T>
Position<T> operator+(Position<T> lhs, const Distance<T> & rhs) {
    lhs += rhs;
    return lhs;
}
template <typename T>
Position<T> operator+(const Distance<T>& lhs, const Position<T> & rhs) {
    return operator+(rhs,lhs);
}

// MINUS STUFF
template <typename T>
Position<T>& Position<T>::operator-=(const Distance<T> & rhs) {
    setX(getX()-rhs.getDiffXi());
    setY(getY()-rhs.getDiffYi());

    return *this;
}

template <typename T>
Position<T> operator-(Position<T> lhs, const Distance<T> & rhs) {
    lhs -= rhs;
    return lhs;
}
template <typename T>
Position<T> operator-(const Distance<T>& lhs, const Position<T> & rhs) {
    return operator-(rhs,lhs);
}
template <typename T>
Distance<T> operator-(const Position<T>& lhs, const Position<T> & rhs) {
    return Distance<T>(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY());
}
