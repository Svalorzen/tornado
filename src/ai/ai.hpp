#ifndef AI_HEADER_FILE
#define AI_HEADER_FILE

class Map;
class Action;

class AI {
    public:
        AI(const Map &);

        const Map & getOwnMap() const;
    private:
        const Map & ownMap_;
};

#endif
