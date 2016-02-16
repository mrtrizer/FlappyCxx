#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjCircle : public GObj, public GColliderCircle, public GViewCircle {
public:
    explicit GObjCircle(R = 0, Pos = {0,0,0});
};

#endif // GOBJCIRCLE_H
