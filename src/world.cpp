#include <cstdlib>

#include "world.h"
#include "ctrl.h"

World::World(Ctrl &flappyCtrl):flappyCtrl(flappyCtrl) {
    srand48(std::time(0));
}

void World::recalc(GObj::DeltaT, const GContext &) {

    auto intersectList = flappySlider->getBird()->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Coin);});
    if (intersectList.size() > 0) {
        getRoot()->removeChild(intersectList.front());
        score++;
    }
//    float x = flappySlider->getPosAbsolute().getX() + 300;
//    if (lastX < x) {
//        groundQueue.push(getRoot()->ADD_CHILD(GDecor,"ground",10,10,POS(lastX - 200,-50,1)));
//        lastX = x + 9.9;
//    }
//    if (groundQueue.size() > 30) {
//        getRoot()->removeChild(groundQueue.front());
//        groundQueue.pop();
//    }
    intersectList = flappySlider->getBird()->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Tube) ||
                typeid(*i) == typeid(Floor);});
    if (intersectList.size() > 0) //TODO: Move up and fix segfault
        flappyCtrl.putSymbol(Ctrl::STOP);
}

void World::init() {
    flappySlider = getRoot()->ADD_CHILD(Slider,POS(-100,0,0));
    setActiveCamera(flappySlider->ADD_CHILD(GObjCamera,100,1.0,500,POS(0,0,0)));
    for (int i = 0; i < 50; i++)
        getRoot()->ADD_CHILD(TubePair,POS(
                                 STEP * i, //x
                                 lrand48() % 10 * 5.0f - 20.0f, //y
                                 1));
//    for (int i = 0; i < 30; i++)
//        groundQueue.push(getRoot()->ADD_CHILD(GDecor,"ground",10,10,POS(-200 + i * 9.9,-50,1)));
}
