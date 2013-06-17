#ifndef OWNABLE_HEADER_FILE
#define OWNABLE_HEADER_FILE

#include <utils/types.hpp>

class Ownable {
    public:
        Ownable();

        void setOwner(ID_t);
        void disown();

        ID_t getOwner() const;

        bool isOwned() const;
    private:
        bool owned_;
        ID_t owner_;
};

#endif
