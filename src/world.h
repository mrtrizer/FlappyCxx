#ifndef FLAPPYWORLD_H
#define FLAPPYWORLD_H

#include <ctime>

#include "core/gworldmodel.h"
#include "core/gobjcamera.h"
#include "slider.h"
#include "bird.h"
#include "tube.h"
#include "floor.h"

class Ctrl;
class Score;

class World: public GWorldModel
{
public:
    World(Ctrl & flappyCtrl);
    inline int getScore() const {return score;}

protected:
    void recalc(GObj::DeltaT, const GContext &) override;
    virtual void init() override;

private:
    double speed;
    Ctrl & flappyCtrl;
    std::shared_ptr<Slider> flappySlider;
    static constexpr float STEP = 50.0f;
    std::queue<std::shared_ptr<GDecor>> groundQueue;
    float lastX = 0;
    int score = 0;
    std::shared_ptr<Score> scorePanel;
};

#endif // FLAPPYWORLD_H
