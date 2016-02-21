#include "flappyworld.h"
#include "flappyctrl.h"

void FlappyWorld::recalc(GObj::DeltaT) {
    if (flappyCamera->getBird()->findIntersectObjs().size() > 0)
        flappyCtrl.putSymbol(GAME_OVER);
}
