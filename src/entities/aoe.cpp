#include "aoe.hpp"

AoE::AoE(Area a) : Entity(a, false, AnimatedSprite()), buildable_(true), shelter_(false) {}

bool AoE::isBuildable() const {
    return buildable_;
}
bool AoE::isShelter() const {
    return shelter_;
}

void AoE::setBuildable(bool b) {
    buildable_ = b;
}
void AoE::setShelter(bool s) {
    shelter_ = s;
}

void AoE::stepUpdate() {

}
