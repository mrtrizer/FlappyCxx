#include "bird.h"

Bird::Bird(Pos pos):
    GObj(pos),
    GColliderCircle(10),
    GViewCustom(5) {

}

void Bird::recalc(DeltaT) {

}
