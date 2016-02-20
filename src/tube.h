#ifndef TUBE_H
#define TUBE_H

#include "shapes/gobjrect.h"

class Tube : public GObjRect {
public:
    Tube(const Pos & pos): GObjRect(10,70,pos) {
    }

    void recalc(DeltaT) override {
    }
};

class TubePair : public GObj {
public:
    using GObj::GObj;
    void init() override {
        ADD_CHILD(Tube,POS(0,10,0));
        ADD_CHILD(Tube,POS(0,-90,0));
    }
};

#endif // TUBE_H
