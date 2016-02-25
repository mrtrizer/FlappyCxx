#include "bird.h"
#include "core/gcontext.h"
#include "shapes/gdecor.h"

Bird::Bird(GPos pos):
    GObj(pos),
    GColliderCircle(RADIUS) {}

void Bird::recalc(GObj::DeltaT deltaT, const GContext &gContext) {
    if (gContext.getMouseEvent() == GContext::CLICK)
        speed = FLAP_SPEED;
    speed = speed + GRAVITY * deltaT;
    this->move({0, speed * deltaT,0});
}

void Bird::init() {
    ADD_CHILD(GDecor,"bird", RADIUS * 2, RADIUS * 2, POS(-RADIUS, -RADIUS, 20));
}
