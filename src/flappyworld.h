#ifndef FLAPPYWORLD_H
#define FLAPPYWORLD_H

#include "core/gworldmodel.h"
#include "flappycamera.h"
#include "bird.h"
#include "tube.h"

class FlappyWorld: public GWorldModel
{
public:
    FlappyWorld() {
        std::srand(1);
    }

    virtual void init() override {
        flappyCamera = std::make_shared<FlappyCamera>(100,1.0,GObj::Pos({0,0,0}));
        getRoot()->addChild<GObjCamera>(flappyCamera);
        setActiveCamera(flappyCamera);
        bird = flappyCamera->ADD_CHILD(Bird,POS(0,0,1));
        for (int i = 0; i < 50; i++)
            getRoot()->ADD_CHILD(TubePair,POS(50.0f * i,std::rand() % 10 * 5.0f - 20.0f,0));
    }

    void flap() {
        bird->flap();
    }

protected:
    void recalc(GObj::DeltaT) override {}

private:
    double speed;
    std::shared_ptr<Bird> bird;
    std::shared_ptr<FlappyCamera> flappyCamera;
};

#endif // FLAPPYWORLD_H
