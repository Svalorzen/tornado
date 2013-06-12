#ifndef ACTION_HEADER_FILE
#define ACTION_HEADER_FILE

#include <memory>

#include <utils/types.hpp>
#include <map/utils/position.hpp>

class Map;
class Entity;

enum class ActionType {
    NONE,
    MOVE_TO,
    PICK_UP,
    PUT_DOWN,
    EAT,
    SLEEP,
    SHELTER,
    BUILD
};

class Action {
    public:
        // We need this one for LUA
        Action();
        Action(ID_t);
        Action(ID_t,ActionType);
        Action(ID_t,ActionType,Position);
        Action(ID_t,ActionType,ID_t,Position);

        void setResolved(bool);
        bool isResolved() const;

        void setActionType(ActionType);
        ActionType getActionType() const;

        void setTargetPosition(Position);
        Position getTargetPosition() const;

        void setActorId(ID_t);
        ID_t getActorId() const;

        void setTargetId(ID_t);
        ID_t getTargetId() const;

        void setTarget(const Entity &);

    private:
        ActionType at_;

        // This variable means if this action has been resolved previously 
        // while doing something else. If so the map should be able to
        // execute the action trivially
        bool resolved_;
        
        Position targetPosition_;

        ID_t actorEntity_;
        ID_t targetEntity_;
};

#endif
