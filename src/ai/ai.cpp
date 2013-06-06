#include "ai.hpp"

AI::AI(const Map & m) : ownMap_(m) {}

const Map & AI::getOwnMap() const {
    return ownMap_;
}
