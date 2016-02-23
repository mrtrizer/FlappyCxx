#ifndef BIRD_H
#define BIRD_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

/// A bird
class Bird: public GObj, public GColliderCircle, public GViewCircle {
public:
    Bird(GPos pos);
    void recalc(DeltaT deltaT, const GContext &) override;

private:
    float speed = 0;
    static constexpr float GRAVITY = -40.0;
    static constexpr float FLAP_SPEED = 30.0;
    static constexpr float RADIUS = 3.0;
    static constexpr float CIRCLE_VERTEX_CNT = 30.0;
};

#endif // BIRD_H
