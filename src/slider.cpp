#include "slider.h"

/// Signal to start show tubes
void Slider::startGame() {
    gameFlag = true;
    tubeStart = -getPos().getX() + 100.0;
    while (tubeCount < TUBES_ON_SCREEN)
        addTube();
}

void Slider::recalc(GObj::DeltaT deltaT, const GContext &) {
    move({-SPEED * deltaT,0,0});
    // check is front of queue is out of borders for tubes and ground
    if (gameFlag)
        if (tubeQueue.front()->getAPos().getX() < TUBES_LEFT_OFFSET) {
            tubeQueue.front()->remove();
            tubeQueue.pop();
            addTube();

        }
    if (groundQueue.front()->getAPos().getX() < TUBES_LEFT_OFFSET) {
        groundQueue.front()->remove();
        groundQueue.pop();
        addGround();
    }
}

void Slider::init() {
    //criate first several ground blocks of ground
    while (groundCount < GROUND_ON_SCREEN)
        addGround();
}

void Slider::addTube() {
    //place tube in random y
    //I use lrand48 becouse rand and srand are absent in Android NDK 22
    tubeQueue.push(ADD_CHILD(MovingTubePair,POS(
                                 STEP * tubeCount + tubeStart, //x
                                 lrand48() % 10 * 5.0f - 20.0f, //y
                                 1)));
    tubeCount++;

}

void Slider::addGround() {
    groundQueue.push(ADD_CHILD(GPresenterSprite,"ground",(float)GROUND_WIDTH,(float)GROUND_WIDTH,POS(
                                   ((float)GROUND_WIDTH - 0.5f) * groundCount + TUBES_LEFT_OFFSET, //x
                                   -50.0, //y
                                   1),2));
    //place a stone?
    if (lrand48() % 2)
        groundQueue.back()->setFrameN(1);
    groundCount++;
}
