#ifndef TUBE_H
#define TUBE_H

#include "shapes/gobjrect.h"

class Tube : public GObjRect {
public:
    Tube(const Pos & pos): GObjRect(10,50,pos) {
    }

    void recalc(DeltaT) override {
//        if (intersectObjList().size() > 0)
//            setColorRGBA({1.0f, 0, 0, 0});
//        else
//            setColorRGBA({1.0f, 1.0f, 1.0f, 1.0f});
    }
};

class TubePair : public GObj {
public:
    using GObj::GObj;
    void init() override {
        ADD_CHILD(Tube,POS(0,10,0));
        ADD_CHILD(Tube,POS(0,-70,0));
    }
};

#endif // TUBE_H
