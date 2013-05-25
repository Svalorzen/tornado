#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/entity.hpp>

class Person : public Entity {
    public:
        Person(int,int, bool);

        void act();

        bool isMale();
    private:
        bool male_;
        std::array<unsigned,10> needs_;

        void goDown();
        void goLeft();
        void goRight();
        void goUp();
};

#endif
