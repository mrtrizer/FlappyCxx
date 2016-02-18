#ifndef BIRD_H
#define BIRD_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

class Bird: public GObj, public GColliderCircle, public GViewCircle {
public:
    Bird(Pos);
    void recalc(DeltaT) override;
};

#endif // BIRD_H
