#ifndef BIRD_H
#define BIRD_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

class GDecor;

class Bird: public GColliderCircle {
public:
    Bird(const GPos &pos);
    void recalc(DeltaT deltaT, const GContext &) override;
    void init() override;
    void startGame();

private:
    float speed = 0;
    static constexpr float GRAVITY = -100.0;
    static constexpr float FLAP_SPEED = 50.0;
    static constexpr float RADIUS = 4.0;
    bool gameFlag = false;
};

#endif // BIRD_H
