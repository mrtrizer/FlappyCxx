#ifndef FLAPPYWORLD_H
#define FLAPPYWORLD_H

#include "core/gworldmodel.h"
#include "core/gobjcamera.h"
#include "slider.h"
#include "bird.h"

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
    std::shared_ptr<Bird> bird;
    double speed = 0.0;
    Ctrl & flappyCtrl;
    std::shared_ptr<GColliderRect> floor;
    std::shared_ptr<Slider> flappySlider;
    std::shared_ptr<GPresenterSprite> info;
    std::queue<std::shared_ptr<GPresenterSprite>> groundQueue;
    int score = 0;
    std::shared_ptr<Score> scorePanel;
    bool gameFlag = false;
};

#endif // FLAPPYWORLD_H
