#include <cstdlib>

#include "world.h"
#include "ctrl.h"
#include "score.h"
#include "bird.h"

World::World(Ctrl &flappyCtrl):flappyCtrl(flappyCtrl) {
    srand48(std::time(0));
}

void World::recalc(GObj::DeltaT, const GContext & gContext) {
    if (!gameFlag)
        if (gContext.getMouseEvent() == GContext::CLICK) {
            bird->startGame();
            flappySlider->startGame();
            getRoot()->removeChild(info);
            gameFlag = true;
        }

    auto coinIntersects = bird->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Coin);});
    if (coinIntersects.size() > 0) {
        getRoot()->removeChild(coinIntersects.front());
        score++;
        scorePanel->setScore(score);
    }

    auto tubeIntersects = bird->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Tube);});
    if (tubeIntersects.size() > 0)
        flappyCtrl.putSymbol(Ctrl::STOP);
    auto floorIntersects = bird->findIntersectObjs([](const GObj::GObjP & i){
        return typeid(*i) == typeid(Floor);});
    if (floorIntersects.size() < 1)
        flappyCtrl.putSymbol(Ctrl::STOP);
}

void World::init() {
    info = getRoot()->ADD_CHILD(GDecor,"tutor",30,30,POS(-15,-15,10));
    bird = getRoot()->ADD_CHILD(Bird,POS(0,0,1));
    getRoot()->ADD_CHILD(GDecor,"background",200,200,POS(-100,-100,0));
    flappySlider = getRoot()->ADD_CHILD(Slider,POS(20,0,0));
    scorePanel = getRoot()->ADD_CHILD(Score,POS(-6.5, 43 -4, 5));
    getRoot()->ADD_CHILD(Floor, 200, POS(-50,-50,0));
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,100,1.0,500,POS(0,0,0)));
}
