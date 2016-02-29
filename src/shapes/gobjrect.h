#ifndef GOBJRECT_H
#define GOBJRECT_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

/// A rectangle with intersection processing.
template <typename Presenter>
class GObjRect: public GColliderRect {
public:
    explicit GObjRect(Size width, Size height, const GPos & pos):
        GColliderRect(width,height,pos)
    {}
    void init() {
        ADD_CHILD(Presenter,getWidth(),getHeight(),GPos(0,0,0));
    }
};

template<>
class GObjRect<GPresenterCircle>: public GColliderRect {
public:
    explicit GObjRect(Size width, Size height, const GPos & pos):
        GColliderRect(width,height,pos)
    {}

    void init() {
        ADD_CHILD(GPresenterCircle,getWidth(),GPos(getWidth() / 2, getHeight() / 2,0));
    }
};

#endif // GOBJRECT_H
