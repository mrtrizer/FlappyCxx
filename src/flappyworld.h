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
    void recalc(GObj::DeltaT) override;
    virtual void init() override {
        flappyCamera = getRoot()->ADD_CHILD(FlappyCamera,100,1.0,POS(0,0,0));
        setActiveCamera(flappyCamera);
        for (int i = 0; i < 50; i++)
            getRoot()->ADD_CHILD(TubePair,POS(
                                     STEP * i, //x
                                     std::rand() % 10 * 5.0f - 20.0f, //y
                                     0));
    }

private:
    double speed;
    FlappyCtrl & flappyCtrl;
    std::shared_ptr<FlappyCamera> flappyCamera;
    static constexpr float STEP = 50.0f;
};

#endif // FLAPPYWORLD_H
