#ifndef ITEM_HEADER_FILE
#define ITEM_HEADER_FILE

#include <entities/entity.hpp>

enum class ItemType {
    FOOD
};

class Item : public Entity {
    public:
        Item(ItemType);        

        void setType(ItemType);
        ItemType getType() const;

        void setLocked(bool);
        bool isLocked() const;

        virtual void stepUpdate();

    private:
        bool locked_;
        ItemType type_;
};

#endif

