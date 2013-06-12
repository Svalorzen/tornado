#ifndef ITEM_HEADER_FILE
#define ITEM_HEADER_FILE

#include <entities/entity.hpp>
#include <entities/utils/lockable.hpp>

enum class ItemType {
    FOOD,
    WOOD
};

class Item : public Entity, public Lockable {
    public:
        Item(ItemType);        

        void setType(ItemType);
        ItemType getType() const;

        virtual void stepUpdate();

    private:
        ItemType type_;
};

#endif

