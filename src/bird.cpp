#include "bird.h"
#include "core/gcontext.h"
#include "shapes/ganimation.h"

Bird::Bird(GPos pos):
    GObj(pos),
    GColliderCircle(RADIUS) {}

void Bird::recalc(GObj::DeltaT deltaT, const GContext &gContext) {
    if (!gameFlag)
        return;
    if (gContext.getMouseEvent() == GContext::CLICK)
        speed = FLAP_SPEED;
    speed = speed + GRAVITY * deltaT;
    this->move({0, speed * deltaT,0});
}

void Bird::init() {
    ADD_CHILD(GAnimation,"bird", RADIUS * 2, RADIUS * 2, POS(-RADIUS, -RADIUS, 20),2,0.3);
}

void Bird::startGame() {
    gameFlag = true;
    speed = FLAP_SPEED;
}
