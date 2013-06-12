#ifndef THINKABLE_HEADER_FILE
#define THINKABLE_HEADER_FILE

#include <entities/entity.hpp>
#include <entities/utils/locker.hpp>

#include <ai/utils/action.hpp>

class Thinkable : public Entity, public Locker {
    public:
        using Entity::Entity;

        void setResult(Action);
        const Action & getResult() const;

    private:
        Action result_;
};

#endif
