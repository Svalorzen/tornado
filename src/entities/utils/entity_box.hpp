#ifndef ENTITY_BOX_HEADER_FILE
#define ENTITY_BOX_HEADER_FILE

#include <cstdlib>

class Map;
class Entity;

class EntityBox {
    public:
        EntityBox();
        operator const Entity *() const;
        const Entity * operator->() const;

    private:
        friend class Map;

        EntityBox(const Entity &, size_t);

        size_t getEntityIndex() const;

        const Entity * entity_;
        size_t entityIndex_;
};


#endif
