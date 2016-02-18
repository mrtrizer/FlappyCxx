#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjCircle : public GObj, public GColliderCircle, public GViewCircle {
public:
    explicit GObjCircle(R r, Pos pos = {0,0,0}):
        GObj(pos),
        GColliderCircle(r),
        GViewCircle(25,r)
    {}
    void recalc(DeltaT) override {
        n += 0.001;
        this->getPosR().x += std::sin(n) / 50.0;
        this->getPosR().y += std::cos(n) / 50.0;
        if (intersectObjList().size() > 0)
            setColorRGBA({1.0f, 0, 0, 0});
        else
            setColorRGBA({1.0f, 1.0f, 1.0f, 1.0f});
    }
private:
    float n = 0;
};

#endif // GOBJCIRCLE_H
