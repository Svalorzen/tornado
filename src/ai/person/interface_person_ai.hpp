#ifndef INTERFACE_PERSON_AI_HEADER_FILE
#define INTERFACE_PERSON_AI_HEADER_FILE

#include <ai/ai.hpp>

class Person;

class InterfacePersonAI : public AI {
    public:
        using AI::AI;

        virtual Action getAction(const Person&) = 0;
};

#endif
