#ifndef COIN_H
#define COIN_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "shapes/gdecor.h"

class Coin :  public GObj, public GColliderCircle
{
public:
    Coin(GPos pos):
        GObj(pos),
        GColliderCircle(RADIUS)
    {}
    void init() override {
        ADD_CHILD(GDecor,"coin", RADIUS * 2, RADIUS * 2, POS(-RADIUS, -RADIUS, 20));
    }
private:
    static constexpr float RADIUS = 3.0;
};

#endif // COIN_H
