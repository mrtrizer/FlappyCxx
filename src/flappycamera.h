#ifndef FLAPPYCAMERA_H
#define FLAPPYCAMERA_H

#include "core/gobjcamera.h"

class FlappyCamera : public GObjCamera {
public:
    using GObjCamera::GObjCamera;

protected:
    void recalc(DeltaT deltaT) override {
        getPosR().x += SPEED * deltaT;
    }
private:
    const double SPEED = 1;
};

#endif // FLAPPYCAMERA_H
