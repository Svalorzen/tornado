#ifndef BASE_PERSON_AI_HEADER_FILE
#define BASE_PERSON_AI_HEADER_FILE

#include <ai/person/interface_person_ai.hpp>

class Person;

class BasePersonAI : public InterfacePersonAI {
    public:
        using InterfacePersonAI::InterfacePersonAI;

        virtual Action getAction(const Person&);
};

#endif
