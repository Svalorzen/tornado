#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/thinkables/thinkable.hpp>

class Action;
class Map;

class Person : public Thinkable {
    public:
        Person(const Map &, bool);

        bool isMale();

        Action getAction();

        virtual void stepUpdate();

    private:
        bool male_;
        static constexpr size_t NEEDS_NUM = 10;
        static constexpr size_t BASIC_NEEDS_NUM = 3;
        static constexpr unsigned NEED_MAX = 10000;
        static constexpr unsigned NEED_NORMAL = 5000;
        static constexpr unsigned NEED_LOW = 2500;
        std::array<unsigned,NEEDS_NUM> needs_;


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
