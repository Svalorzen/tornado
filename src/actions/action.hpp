#ifndef ACTION_HEADER_FILE
#define ACTION_HEADER_FILE

class Entity;

enum class ActionType {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    PICK_UP,
    PUT_DOWN,
    EAT,
    SLEEP
};

enum class ActionResolver {
    OK,
    DENIED,
    SPECIAL
};

class Action {
    public:
        Action(Entity &, ActionType);

        Entity & getEntity();

        ActionType getActionType() const;
    private:
        Entity & entity_;
        ActionType at_;
};

#endif
