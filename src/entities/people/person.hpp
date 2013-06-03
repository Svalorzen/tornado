#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/entity.hpp>
#include <actions/action.hpp>

class Map;

class Person : public Entity {
    public:
        Person(Map&,bool);

        bool isMale();

        Action getAction();

        virtual void stepUpdate();
    private:
        bool male_;
        std::array<unsigned,10> needs_;
};

#endif
