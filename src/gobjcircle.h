#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjCircle : public GObj, public GColliderCircle, public SELECT_VIEW(GViewCircle) {
public:
    explicit GObjCircle(R = 0, Pos = {0,0,0});
protected:
    void recalc(DeltaT) override {
        n += 0.001;
        getPosR().x += std::cos(n) / 1000.0;
        getPosR().y += std::sin(n) / 1000.0;
    }
private:
    double n = 0;
};

#endif // GOBJCIRCLE_H
