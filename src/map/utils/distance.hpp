#ifndef DISTANCE_HEADER_FILE
#define DISTANCE_HEADER_FILE

class Distance {
    public:
        Distance();
        Distance(int, int);

        unsigned getDiffXu() const;
        unsigned getDiffYu() const;

        int getDiffXi() const;
        int getDiffYi() const;

        unsigned getDistance() const;

        void setDiffX(int);
        void setDiffY(int);

        Distance& operator+=(const Distance&);
        Distance& operator-=(const Distance&);
        Distance& operator/=(float);
        Distance& operator*=(float);

    private:
        int diffX_;
        int diffY_;
};

bool operator==(const Distance&, const Distance&);
bool operator!=(const Distance&, const Distance&);

bool operator<(const Distance&, const Distance&);
bool operator<=(const Distance&, const Distance&);

bool operator>(const Distance&, const Distance&);
bool operator>=(const Distance&, const Distance&);

Distance operator+(Distance, const Distance&);
Distance operator-(Distance, const Distance&);
Distance operator-(Distance);

Distance operator*(Distance, float);
Distance operator*(float, Distance);

Distance operator/(Distance, float);
Distance operator/(float, Distance);

#endif
