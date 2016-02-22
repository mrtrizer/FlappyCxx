#include "flappyworld.h"
#include "flappyctrl.h"

FlappyWorld::FlappyWorld(FlappyCtrl &flappyCtrl):flappyCtrl(flappyCtrl) {
    std::srand(std::time(0));
}

void FlappyWorld::recalc(GObj::DeltaT, GContext) {
    auto intersectList = flappySlider->getBird()->findIntersectObjs([](const GObj::GObjP & i){return typeid(*i) == typeid(Tube);});
    if (intersectList.size() > 0)
        flappyCtrl.putSymbol(FlappyCtrl::STOP);
}

void FlappyWorld::init() {
    flappySlider = getRoot()->ADD_CHILD(FlappySlider,POS(-100,0,0));
    setActiveCamera(flappySlider->ADD_CHILD(GObjCamera,100,1.0,500,POS(0,0,0)));
    for (int i = 0; i < 50; i++)
        getRoot()->ADD_CHILD(TubePair,POS(
                                 STEP * i, //x
                                 std::rand() % 10 * 5.0f - 20.0f, //y
                                 0));
}
