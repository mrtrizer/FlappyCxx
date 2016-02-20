#ifndef BIRD_H
#define BIRD_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

class Bird: public GObj, public GColliderCircle, public GViewCircle {
public:
    Bird(GPos pos):
        GObj(pos),
        GColliderCircle(RADIUS),
        GViewCircle(CIRCLE_VERTEX_CNT, RADIUS) {}

    void recalc(DeltaT deltaT) override {
        if (findIntersectObjs().size() > 0)
            setColorRGBA({1.0f, 0, 0, 0});
        else
            setColorRGBA({1.0f, 1.0f, 1.0f, 1.0f});
        speed = speed + GRAVITY * deltaT;
        this->getPos().move({0, speed * deltaT,0});
    }

    void flap() {
        speed = FLAP_SPEED;
    }

private:
    float speed;
    static constexpr float GRAVITY = -40.0;
    static constexpr float FLAP_SPEED = 30.0;
    static constexpr float RADIUS = 3.0;
    static constexpr float CIRCLE_VERTEX_CNT = 30.0;
};

#endif // BIRD_H
