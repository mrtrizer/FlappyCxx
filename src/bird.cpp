#include "bird.h"
#include "core/gcontext.h"

Bird::Bird(GPos pos):
    GObj(pos),
    GColliderCircle(RADIUS),
    GViewCircle(CIRCLE_VERTEX_CNT, RADIUS) {}

void Bird::recalc(GObj::DeltaT deltaT, const GContext &gContext) {
    if (gContext.getMouseEvent() == GContext::CLICK)
        speed = FLAP_SPEED;
    speed = speed + GRAVITY * deltaT;
    this->getPos().move({0, speed * deltaT,0});
}
