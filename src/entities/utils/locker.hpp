#ifndef LOCKER_HEADER_FILE
#define LOCKER_HEADER_FILE

#include <utils/types.hpp>

class Locker {
    public:
        Locker();
        
        void lock(ID_t); 
        void unlock();

        ID_t getLocked() const;

        bool isLocking() const;
    private:
        bool locking_;
        ID_t locked_;
};

#endif
