#ifndef TUBE_H
#define TUBE_H

#include "shapes/gobjrect.h"
#include "coin.h"

class Tube : public GObj, public GColliderRect, public GPresenterSprite {
public:
    Tube(const GPos & pos):
        GObj(pos),
        GColliderRect(10,70),
        GPresenterSprite("tube",10,70)
    {}
};

class TubePair : public GObj {
public:
    using GObj::GObj;
    void init() override {
        ADD_CHILD(Tube,POS(0,10,0));
        ADD_CHILD(Tube,POS(0,-90,0));
        ADD_CHILD(Coin,POS(5,-5,0));
    }

};

#endif // TUBE_H
