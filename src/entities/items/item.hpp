#ifndef ITEM_HEADER_FILE
#define ITEM_HEADER_FILE

#include <entities/entity.hpp>

class Map;

enum class ItemType {
    FOOD
};

class Item : public Entity {
    public:
        Item(const Map *, ItemType);        
        ItemType getType() const;
        bool isLocked() const;
        void setLocked(bool);

        virtual void stepUpdate();
    private:
        bool locked_;
        ItemType type_;
};

#endif

