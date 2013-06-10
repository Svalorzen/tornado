#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <utils/enum_string.hpp>

#include <entities/thinkable.hpp>

class Action;
class Map;

class Person : public Thinkable {
    public:
        static constexpr size_t NEEDS_NUM = 10;
        static constexpr size_t BASIC_NEEDS_NUM = 3;
        //static constexpr unsigned NEED_LIMITS[] = {0,2500,5000,10000};
        static constexpr unsigned NEED_PRIORITIES[] = {2500,5000,10000};

        static constexpr entry NEEDS[] = {
            { "sleep",      0 },
            { "hunger",     1 },
            { "cold",       2 },

            { "housing",    3 },
            { "reproduction",   4 },
            { "infrastructure", 5 },
            { "luxury",     6 }
        };

        Person(bool);

        void setMale(bool);
        bool isMale() const;

        // setNeeds, atm we don't need it..
        const std::array<unsigned,NEEDS_NUM> & getNeeds() const;

        virtual void stepUpdate();
    private:
        bool male_;
        std::array<unsigned,NEEDS_NUM> needs_;
};

#endif
