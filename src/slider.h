#ifndef FLAPPYSLIDER_H
#define FLAPPYSLIDER_H

#include <queue>
#include <ctime>
#include <cstdlib>

#include "core/gobj.h"
#include "shapes/gdecor.h"
#include "tube.h"
#include "floor.h"

/// Contains a bird and an instance of GObjCamera (added in FlappyWorld::init)
class Slider: public GObj {
public:
    using GObj::GObj;

    void startGame() {
        gameFlag = true;
        tubeStart = getPos().getX() + 100.0;
        for (; tubeCount < TUBES_ON_SCREEN; )
            addTube();
    }

protected:
    void recalc(DeltaT deltaT, const GContext &) override {
        move({-SPEED * deltaT,0,0});
        if (gameFlag)
            if (tubeQueue.front()->getAPos().getX() < TUBES_LEFT_OFFSET) {
                removeChild(tubeQueue.front());
                tubeQueue.pop();
                addTube();

            }
        if (groundQueue.front()->getAPos().getX() < TUBES_LEFT_OFFSET) {
            removeChild(groundQueue.front());
            groundQueue.pop();
            addGround();
        }
    }

    void init() {
        for (; groundCount < GROUND_ON_SCREEN; )
            addGround();
    }

private:
    static constexpr float SPEED = 20.0;
    static constexpr float STEP = 50.0f;
    static constexpr int TUBES_ON_SCREEN = 7;
    static constexpr float TUBES_LEFT_OFFSET = -150.0;
    static constexpr float GROUND_WIDTH = 10.0;
    static constexpr int GROUND_ON_SCREEN = 25;

    std::queue<std::shared_ptr<MovingTubePair>> tubeQueue;
    std::queue<std::shared_ptr<GDecor>> groundQueue;
    int tubeCount = 0;
    int groundCount = 0;
    bool gameFlag = false;
    float tubeStart = 0.0;

    void addTube() {
        tubeQueue.push(ADD_CHILD(MovingTubePair,POS(
                                 STEP * tubeCount + tubeStart, //x
                                 lrand48() % 10 * 5.0f - 20.0f, //y
                                 1)));
        tubeCount++;

    }
    void addGround() {
        groundQueue.push(ADD_CHILD(GDecor,"ground",(float)GROUND_WIDTH,(float)GROUND_WIDTH,POS(
                                 ((float)GROUND_WIDTH - 0.5f) * groundCount + TUBES_LEFT_OFFSET, //x
                                 -50.0, //y
                                 1),2));
        if (lrand48() % 2)
            groundQueue.back()->setFrameN(1);
        groundCount++;
    }
};

#endif // FLAPPYSLIDER_H
