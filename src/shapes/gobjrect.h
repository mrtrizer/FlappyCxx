#ifndef GOBJRECT_H
#define GOBJRECT_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

class GObjRect: public GObj, public GColliderRect, public GPresenterRect {
public:
    explicit GObjRect(Size width, Size height, GPos pos):
        GObj(pos),
        GColliderRect(width,height),
        GPresenterRect(width, height)
    {}
    virtual ~GObjRect(){}
};

#endif // GOBJRECT_H
