#include "bird.h"

Bird::Bird(Pos pos):
    GObj(pos),
    GColliderCircle(10),
    GViewCircle(5,1) {

}

void Bird::recalc(DeltaT) {

}
