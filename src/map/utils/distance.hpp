#ifndef DISTANCE_HEADER_FILE
#define DISTANCE_HEADER_FILE

template <typename T>
class Distance {
    public:
        Distance();
        Distance(T, T);

        template <typename M>
        Distance(const Distance<M> &);

        T getDiffXu() const;
        T getDiffYu() const;

        T getDiffXi() const;
        T getDiffYi() const;

        T getDistance() const;

        void setDiffX(T);
        void setDiffY(T);

        Distance& operator+=(const Distance<T>&);
        Distance& operator-=(const Distance<T>&);
        Distance& operator/=(float);
        Distance& operator*=(float);

    private:
        T diffX_;
        T diffY_;
};

template <typename T>
bool operator==(const Distance<T>&, const Distance<T>&);
template <typename T>
bool operator!=(const Distance<T>&, const Distance<T>&);

template <typename T>
bool operator<(const Distance<T>&, const Distance<T>&);
template <typename T>
bool operator<=(const Distance<T>&, const Distance<T>&);

template <typename T>
bool operator>(const Distance<T>&, const Distance<T>&);
template <typename T>
bool operator>=(const Distance<T>&, const Distance<T>&);

template <typename T>
Distance<T> operator+(Distance<T>, const Distance<T>&);
template <typename T>
Distance<T> operator-(Distance<T>, const Distance<T>&);
template <typename T>
Distance<T> operator-(Distance<T>);

template <typename T>
Distance<T> operator*(Distance<T>, float);
template <typename T>
Distance<T> operator*(float, Distance<T>);

template <typename T>
Distance<T> operator/(Distance<T>, float);
template <typename T>
Distance<T> operator/(float, Distance<T>);

#include "distance.tpp"

#endif
