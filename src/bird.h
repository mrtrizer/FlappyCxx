#ifndef BIRD_H
#define BIRD_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class Bird: public GObj, public GColliderCircle, public SELECT_VIEW(GViewCircle) {
public:
    Bird(Pos);
    void recalc(DeltaT) override;
};

#endif // BIRD_H
