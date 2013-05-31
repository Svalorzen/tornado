#ifndef POSITION_HEADER_FILE
#define POSITION_HEADER_FILE

class Position {
    public:
        Position();

        int getX() const;
        int getY() const;

        void setX(int);
        void setY(int);

        Position& operator+=(const Position&);
        Position& operator-=(const Position&);

    private:
        int x_;
        int y_;
};

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

#endif
