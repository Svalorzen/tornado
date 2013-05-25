#ifndef PERSON_HEADER_FILE
#define PERSON_HEADER_FILE

#include <entities/entity.hpp>

class Person : public Entity {
    public:
        Person(int,int, bool);

        bool isMale();
    private:
        bool male;
        std::array<unsigned,10> needs;
};

#endif
