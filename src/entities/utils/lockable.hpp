#ifndef LOCKABLE_HEADER_FILE
#define LOCKABLE_HEADER_FILE

#include <entities/utils/entity_box.hpp>

class Lockable {
    public:
        Lockable();

        void lock(EntityBox);
        void unlock();

        EntityBox & getLocker();
        const EntityBox & getLocker() const;

        bool isLocked() const;
    private:
        bool locked_;
        EntityBox locker_;
};

#endif
