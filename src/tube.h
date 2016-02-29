#ifndef TUBE_H
#define TUBE_H

#include "shapes/gobjrect.h"

class Coin : public GColliderCircle
{
public:
    Coin(GPos pos):
        GColliderCircle(3.0,pos)
    {}
    void init() override;
};

class Tube : public GObjRect<GPresenterSprite> {
public:
    Tube(const GPos & pos):
        GObjRect("tube",10,70,pos)
    {}
};

class TubePair : public GObj {
public:
    using GObj::GObj;
    virtual ~TubePair(){}
    void init() override;
};

class MovingTubePair: public TubePair {
public:
    using TubePair::TubePair;
    void recalc(DeltaT deltaT, const GContext &);
private:
    float dir = 1;
    static constexpr float SPEED = 5.0;
};

#endif // TUBE_H
