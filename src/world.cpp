#include <cstdlib>

#include "world.h"
#include "ctrl.h"
#include "score.h"

World::World(Ctrl &flappyCtrl):flappyCtrl(flappyCtrl) {
    srand48(std::time(0));
}

void World::recalc(GObj::DeltaT, const GContext &) {
    auto intersectList = flappySlider->getBird()->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Tube) ||
                typeid(*i) == typeid(Floor);});
    if (intersectList.size() > 0)
        flappyCtrl.putSymbol(Ctrl::STOP);

    intersectList = flappySlider->getBird()->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Coin);});
    if (intersectList.size() > 0) {
        getRoot()->removeChild(intersectList.front());
        score++;
        scorePanel->setScore(score);
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
}

void World::init() {
    flappySlider = getRoot()->ADD_CHILD(Slider,POS(-100,0,0));
    scorePanel = flappySlider->ADD_CHILD(Score,POS(-6.5, 43 -4, 5));
    setActiveCamera(flappySlider->ADD_CHILD(GObjCamera,100,1.0,500,POS(0,0,0)));
    for (int i = 0; i < 10; i++)
        getRoot()->ADD_CHILD(MovingTubePair,POS(
                                 STEP * i, //x
                                 lrand48() % 10 * 5.0f - 20.0f, //y
                                 1));
//    for (int i = 0; i < 30; i++)
//        groundQueue.push(getRoot()->ADD_CHILD(GDecor,"ground",10,10,POS(-200 + i * 9.9,-50,1)));
}
