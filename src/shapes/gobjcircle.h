#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

/// A circle with an intersection processing.
template <typename Presenter>
class GObjCircle : public GColliderCircle {
public:
    explicit GObjCircle(R r, const GPos &  pos = {0,0,0}):
        GColliderCircle(r,pos)
    {}
    void init() {
        ADD_CHILD(Presenter,getR() * 2,getR() * 2,GPos(-getR(),-getR(),0));
    }
};

template<>
class GObjCircle<GPresenterCircle>: public GColliderCircle {
public:
    explicit GObjCircle(R r, const GPos &  pos = {0,0,0}):
        GColliderCircle(r,pos)
    {}

    void init() {
        ADD_CHILD(GPresenterCircle,getR(),GPos(0,0,0));
    }
};

#endif // GOBJCIRCLE_H
