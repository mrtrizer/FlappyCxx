#ifndef FLAPPYWORLD_H
#define FLAPPYWORLD_H

#include <ctime>

#include "core/gworldmodel.h"
#include "flappycamera.h"
#include "bird.h"
#include "tube.h"

class FlappyCtrl;

class FlappyWorld: public GWorldModel
{
public:
    FlappyWorld(FlappyCtrl & flappyCtrl):flappyCtrl(flappyCtrl) {
        std::srand(std::time(0));
    }

    void flap() {
        flappyCamera->getBird()->flap();
    }

protected:
    void recalc(GObj::DeltaT, GContext) override;
    virtual void init() override;

private:
    double speed;
    FlappyCtrl & flappyCtrl;
    std::shared_ptr<FlappyCamera> flappyCamera;
    static constexpr float STEP = 50.0f;
};

#endif // FLAPPYWORLD_H
