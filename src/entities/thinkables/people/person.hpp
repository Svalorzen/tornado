#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/thinkables/thinkable.hpp>
#include <actions/action.hpp>

class Map;

class Person : public Thinkable {
    public:
        Person(const Map &, bool);

        bool isMale();

        Action getAction();

        virtual void stepUpdate();

        Map getOwnMap();        

    private:
        bool male_;
        std::array<unsigned,10> needs_;

        enum {
            // Needs indexes;
            // BASIC
            SLEEP=          0,
            HUNGER=         1,
            COLD=           2,
            // ADVANCED
            HOUSING=        3,
            REPRODUCTION=   4,
            INFRASTRUCTURE= 5,
            // MORE
            LUXURY=         6
        };
};

#endif
