#ifndef COIN_H
#define COIN_H

#include "core/gobj.h"
#include "core/gcollider.h"

class Coin : public GColliderCircle
{
public:
    Coin(GPos pos):
        GColliderCircle(RADIUS,pos)
    {}
    void init() override;
private:
    static constexpr float RADIUS = 3.0;
};

#endif // COIN_H
