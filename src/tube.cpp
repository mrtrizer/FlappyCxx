#include "tube.h"
#include "core/ganimation.h"

void Coin::init() {
    ADD_CHILD(GAnimation,"coin", getR() * 2, getR() * 2, POS(-getR(), -getR(), 20),2,0.3);
}

void TubePair::init() {
    ADD_CHILD(Tube,POS(0,10,0));
    ADD_CHILD(Tube,POS(0,-90,0));
    ADD_CHILD(Coin,POS(5,-5,0));
}

void MovingTubePair::recalc(GObj::DeltaT deltaT, const GContext &) {
    if ((getPos().getY() > 30.0) || (getPos().getY() < -30))
        dir = -dir;
    move(GPos(0,dir * SPEED * deltaT,0));
}
