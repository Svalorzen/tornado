#ifndef OWNER_HEADER_FILE
#define OWNER_HEADER_FILE

#include <utils/types.hpp>

class Owner {
    public:
        Owner();
        
        void own(ID_t); 
        void disown();

        ID_t getOwned() const;

        bool isOwner() const;
    private:
        bool owner_;
        ID_t owned_;
};

#endif
