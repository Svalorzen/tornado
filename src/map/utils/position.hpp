#ifndef POSITION_HEADER_FILE
#define POSITION_HEADER_FILE

#include <utils/hashing.hpp>
#include <iostream>

template <typename T>
class Distance;

template <typename T>
class Position {
    public:
        Position();
        Position(T, T);
        template <typename M>
        Position(const Position<M> &);

        T getX() const;
        T getY() const;

        Position up() const;
        Position down() const;
        Position left() const;
        Position right() const;

        void print() const { std::cout << "{ X: " << getX() << " , Y: " << getY() << " }"; }

        void setX(T);
        void setY(T);

        // This is for Positions with a different type
        template <typename M>
        Position& operator=(const Position<M>&);

        Position& operator+=(const Distance<T>&);
        Position& operator-=(const Distance<T>&);

    private:
        T x_;
        T y_;
};


template <typename T>
bool operator==(const Position<T> & lhs, const Position<T>& rhs );
template <typename T>
bool operator!=(const Position<T> & lhs, const Position<T>& rhs );

template <typename T>
Position<T> operator+(Position<T> lhs, const Distance<T> & rhs);
template <typename T>
Position<T> operator+(const Distance<T> & lhs, const Position<T> & rhs);

template <typename T>
Position<T> operator-(Position<T> lhs, const Distance<T> & rhs);
template <typename T>
Position<T> operator-(const Distance<T> & lhs, const Position<T> & rhs);
template <typename T>
Distance<T> operator-(const Position<T> & lhs, const Position<T> & rhs);

// Hashing specialization
namespace std {
    template <>
    template <typename T>
    struct hash<Position<T>> {
        inline size_t operator()(const Position<T>& p) const { 
            size_t seed = 0;
            Utils::hash_combine(seed, p.getX());
            Utils::hash_combine(seed, p.getY());
            return seed;
        }
    };
}

#include "position.tpp"

#endif
