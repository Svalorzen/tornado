#ifndef SELECTOR_HEADER_FILE
#define SELECTOR_HEADER_FILE

#include <entities/utils/entity_box.hpp>

class Locker {
    public:
        Locker();
        
        void lock(EntityBox); 
        void unlock();

        EntityBox & getLocked();
        const EntityBox & getLocked() const;

        bool isLocking() const;
    private:
        bool locking_;
        EntityBox locked_;
};

#endif
