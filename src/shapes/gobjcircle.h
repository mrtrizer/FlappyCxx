#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

/// A circle with an intersection processing.
class GObjCircle : public GObj, public GColliderCircle, public GPresenterCircle {
public:
    explicit GObjCircle(R r, GPos pos = {0,0,0}):
        GObj(pos),
        GColliderCircle(r),
        GPresenterCircle(r)
    {}
};

#endif // GOBJCIRCLE_H
