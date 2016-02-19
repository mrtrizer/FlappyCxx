#ifndef BIRD_H
#define BIRD_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

class Bird: public GObj, public GColliderCircle, public GViewCircle {
public:
    Bird(Pos pos):
        GObj(pos),
        GColliderCircle(3),
        GViewCircle(30,3) {

    }

    void recalc(DeltaT deltaT) override {
        if (intersectObjList().size() > 0)
            setColorRGBA({1.0f, 0, 0, 0});
        else
            setColorRGBA({1.0f, 1.0f, 1.0f, 1.0f});
        speed = speed + G * deltaT;
        this->getPosR().y += speed * deltaT;
    }

    void flap() {
        speed = 1.0;
    }

private:
    float speed;
    float acc;
    const float G = -0.05;
};

#endif // BIRD_H
