#ifndef LOCKABLE_HEADER_FILE
#define LOCKABLE_HEADER_FILE

#include <utils/types.hpp>

class Lockable {
    public:
        Lockable();

        void lock(ID_t);
        void unlock();

        ID_t getLocker() const;

        bool isLocked() const;
    private:
        bool locked_;
        ID_t locker_;
};

#endif
