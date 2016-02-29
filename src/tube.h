#ifndef TUBE_H
#define TUBE_H

#include "shapes/gobjrect.h"
#include "coin.h"

class Tube : public GColliderRect {
public:
    Tube(const GPos & pos):
        GColliderRect(10,70,pos)
    {}
    void init() {
        ADD_CHILD(GPresenterSprite,"tube",10,70);
    }
};

class TubePair : public GObj {
public:
    using GObj::GObj;
    virtual ~TubePair(){}
    void init() override {
        ADD_CHILD(Tube,POS(0,10,0));
        ADD_CHILD(Tube,POS(0,-90,0));
        ADD_CHILD(Coin,POS(5,-5,0));
    }

};

class MovingTubePair: public TubePair {
public:
    using TubePair::TubePair;
    void recalc(DeltaT deltaT, const GContext &) {
        if ((getPos().getY() > 30.0) || (getPos().getY() < -30))
            dir = -dir;
        move(GPos(0,dir * SPEED * deltaT,0));
    }
private:
    float dir = 1;
    static constexpr float SPEED = 5.0;
};

#endif // TUBE_H
