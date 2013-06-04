#ifndef ACTION_HEADER_FILE
#define ACTION_HEADER_FILE

#include <map/utils/position.hpp>

class Entity;

enum class ActionType {
    MOVE_TO,
    PICK_UP,
    PUT_DOWN,
    EAT,
    SLEEP,
    SHELTER
};

class Action {
    public:
        Action(Entity &, ActionType);
        Action(Entity &, ActionType, Position);
        Action(Entity &, ActionType, Entity*);

        bool isResolved() const;
        void setResolved(bool);

        // Base entity can't change
        Entity & getEntity();
        // Nor can the action type (yet?)
        ActionType getActionType() const;

        void setTargetPosition(Position);
        void setTargetEntity(Entity*);

        Position getTargetPosition() const;
        Entity* getTargetEntity();
    private:
        Entity & entity_;
        ActionType at_;

        // This variable means if this action has been resolved previously while doing something else
        // If so the map should be able to execute the action trivially
        bool resolved_;
        
        Position targetPosition_;
        Entity * targetEntity_;
};

#endif
