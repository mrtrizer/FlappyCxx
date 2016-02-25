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
    n++;
    if (n > 20) {
        n = 0;
        flag = flag == 1?0:1;
        birdSprite->setFrameN(flag);
    }
}

void Bird::init() {
    birdSprite = ADD_CHILD(GDecor,"bird_anim", RADIUS * 2, RADIUS * 2, POS(-RADIUS, -RADIUS, 20),2);
}
