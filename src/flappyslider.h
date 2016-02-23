#ifndef FLAPPYSLIDER_H
#define FLAPPYSLIDER_H

#include "core/gobj.h"
#include "bird.h"

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
        bird = ADD_CHILD(Bird,POS(0,0,1));
    }

private:
    std::shared_ptr<Bird> bird;
    static constexpr float SPEED = 20.0;
};

#endif // FLAPPYSLIDER_H
