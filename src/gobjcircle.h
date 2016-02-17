#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjCircle : public GObj, public GColliderCircle, public SELECT_VIEW(GViewCircle) {
public:
    explicit GObjCircle(R r, Pos pos = {0,0,0}):
        GObj(pos),
        GColliderCircle(r),
        GViewCustom(25,r)
    {}
};

#endif // GOBJCIRCLE_H
