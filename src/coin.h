#ifndef COIN_H
#define COIN_H

#include "core/gobj.h"
#include "core/gcollider.h"

class Coin :  public GObj, public GColliderCircle
{
public:
    Coin(GPos pos):
        GObj(pos),
        GColliderCircle(RADIUS)
    {}
    void init() override;
private:
    static constexpr float RADIUS = 3.0;
};

#endif // COIN_H
