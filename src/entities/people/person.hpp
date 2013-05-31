#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/entity.hpp>
#include <actions/action.hpp>

class Map;

class Person : public Entity {
    public:
        Person(Map&,int,int,bool);

        void act();

        bool isMale();

        Action getAction();
    private:
        bool male_;
        std::array<unsigned,10> needs_;

        void goDown();
        void goLeft();
        void goRight();
        void goUp();
};

#endif
