#ifndef ACTION_HEADER_FILE
#define ACTION_HEADER_FILE

#include <memory>

#include <map/utils/position.hpp>
#include <ai/utils/entity_box.hpp>

class Map;

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
        Action(ActionType);
        Action(ActionType,Position);
        Action(ActionType,EntityBox);

        void setResolved(bool);
        bool isResolved() const;

        void setActionType(ActionType);
        ActionType getActionType() const;

        void setTargetPosition(Position);
        Position getTargetPosition() const;

        void setEntityBox(EntityBox);
        const EntityBox getEntityBox() const;
    private:
        ActionType at_;

        // This variable means if this action has been resolved previously 
        // while doing something else. If so the map should be able to
        // execute the action trivially
        bool resolved_;
        
        Position targetPosition_;

        EntityBox targetEntity_;
};

#endif
