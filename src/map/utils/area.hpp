#ifndef MAP_AREA_HEADER_FILE
#define MAP_AREA_HEADER_FILE

#include <initializer_list>
#include <array>
#include <bitset>
#include <string>

class Area {
    public:
        static const size_t maxSize = 8u;

        Area(std::initializer_list<std::string>); 

        const std::array<std::bitset<maxSize>,maxSize> & getArea() const;

        unsigned getMaxH() const;
        unsigned getMaxW() const;

        Area& operator+=(const Area&);
        Area& operator-=(const Area&);

    private:
        std::array<std::bitset<maxSize>,maxSize> area_; 
        unsigned maxH_;
        unsigned maxW_;

        void normalize();
};

inline Area& Area::operator+=(const Area& rhs) {
    for ( size_t i = 0; i < area_.size(); i++ )
        area_[i] |= rhs.area_[i];

    maxW_ = maxW_ > rhs.maxW_ ? maxW_ : rhs.maxW_ ;
    maxH_ = maxH_ > rhs.maxH_ ? maxH_ : rhs.maxH_ ;

    return *this;
}
inline Area operator+(Area lhs, const Area& rhs) {
    lhs += rhs;
    return lhs;
}

inline Area& Area::operator-=(const Area& rhs) {
    for ( size_t i = 0; i < area_.size(); i++ )
        area_[i] ^= ( area_[i] & rhs.area_[i] );

    normalize();

    return *this;
}
inline Area operator-(Area lhs, const Area& rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename T>
inline T reverseBitmap(T v) {
    auto r = v;

    size_t s = v.size() - 1;
    for (v >>= 1; v.any(); v >>= 1) {   
        r <<= 1;
        r[0] = v[0];
        s--;
    }
    r <<= s; // shift when v's highest bits are zero
    
    return r;
}

#endif
