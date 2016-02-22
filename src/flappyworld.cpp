#include "flappyworld.h"
#include "flappyctrl.h"

void FlappyWorld::recalc(GObj::DeltaT, GContext) {
    if (flappyCamera->getBird()->findIntersectObjs().size() > 0)
        flappyCtrl.putSymbol(FlappyCtrl::STOP);
}

void FlappyWorld::init() {
    flappyCamera = getRoot()->ADD_CHILD(FlappyCamera,100,1.0,POS(0,0,0));
    setActiveCamera(flappyCamera);
    for (int i = 0; i < 50; i++)
        getRoot()->ADD_CHILD(TubePair,POS(
                                 STEP * i, //x
                                 std::rand() % 10 * 5.0f - 20.0f, //y
                                 0));
}
