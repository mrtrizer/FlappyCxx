#ifndef FLAPPYCAMERA_H
#define FLAPPYCAMERA_H

#include "core/gobjcamera.h"
#include "bird.h"

class FlappyCamera : public GObjCamera {
public:
    using GObjCamera::GObjCamera;

    inline std::shared_ptr<Bird> getBird() {return bird;}

protected:
    void recalc(DeltaT deltaT, GContext) override {
        getPos().move({SPEED * deltaT,0,0});
    }

    void init() {
        bird = ADD_CHILD(Bird,POS(0,0,1));
    }

private:
    static constexpr float SPEED = 20.0;
    std::shared_ptr<Bird> bird;
};

#endif // FLAPPYCAMERA_H
