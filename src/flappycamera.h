#ifndef FLAPPYCAMERA_H
#define FLAPPYCAMERA_H

#include "core/gobjcamera.h"

class FlappyCamera : public GObjCamera {
public:
    using GObjCamera::GObjCamera;

protected:
    void recalc(DeltaT deltaT) override {
        getPos().move({SPEED * deltaT,0,0});
    }
private:
    const float SPEED = 20.0;
};

#endif // FLAPPYCAMERA_H
