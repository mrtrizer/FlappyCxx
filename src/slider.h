#ifndef FLAPPYSLIDER_H
#define FLAPPYSLIDER_H

#include <queue>
#include <ctime>
#include <cstdlib>

#include "core/gobj.h"
#include "core/gpresenter.h"
#include "tube.h"

/// Contains a field moving under the bird and camera.
/// Automatic removed and adds new tubes and blocks of ground.
class Slider: public GObj {
public:
    using GObj::GObj;

    void startGame();
protected:
    void recalc(DeltaT deltaT, const GContext &) override;
    void init();

private:
    static constexpr float SPEED = 20.0;
    static constexpr float STEP = 50.0f;
    static constexpr int TUBES_ON_SCREEN = 7;
    static constexpr float TUBES_LEFT_OFFSET = -150.0;
    static constexpr float GROUND_WIDTH = 10.0;
    static constexpr int GROUND_ON_SCREEN = 25;

    std::queue<std::shared_ptr<MovingTubePair>> tubeQueue;
    std::queue<std::shared_ptr<GPresenterSprite>> groundQueue;
    int tubeCount = 0;
    int groundCount = 0;
    bool gameFlag = false;
    float tubeStart = 0.0;

    void addTube();
    void addGround();
};

#endif // FLAPPYSLIDER_H
