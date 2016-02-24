#ifndef FLAPPYSLIDER_H
#define FLAPPYSLIDER_H

#include <queue>

#include "core/gobj.h"
#include "shapes/gdecor.h"
#include "bird.h"
#include "floor.h"

/// Contains a bird and an instance of GObjCamera (added in FlappyWorld::init)
class FlappySlider: public GObj {
public:
    using GObj::GObj;

    inline std::shared_ptr<Bird> getBird() {return bird;}

protected:
    void recalc(DeltaT deltaT, const GContext &) override {
        getPos().move({SPEED * deltaT,0,0});
    }

    void init() {
        ADD_CHILD(GDecor,"background",200,200,POS(-100,-100,0));
        ADD_CHILD(Floor,300,POS(-150,-60,0));
        ADD_CHILD(Floor,300,POS(-150,50,0));
        bird = ADD_CHILD(Bird,POS(0,0,1));
        for (int i = 0; i < 30; i++)
            ADD_CHILD(GDecor,"ground",10,10,POS(-200 + i * 9.9,-50,1));
    }

private:
    std::shared_ptr<Bird> bird;
    static constexpr float SPEED = 20.0;
};

#endif // FLAPPYSLIDER_H
