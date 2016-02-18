#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

class GObjCircle : public GObj, public GColliderCircle, public GViewCircle {
public:
    explicit GObjCircle(R r, Pos pos = {0,0,0}):
        GObj(pos),
        GColliderCircle(r),
        GViewCircle(25,r)
    {}
};

#endif // GOBJCIRCLE_H
