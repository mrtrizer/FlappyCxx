#ifndef GOBJRECT_H
#define GOBJRECT_H

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gview.h"

class GObjRect: public GObj, public GColliderRect, public GViewRect {
public:
    explicit GObjRect(Size width, Size height, Pos pos):
        GObj(pos),
        GColliderRect(width,height),
        GViewRect(width, height)
    {}
    virtual ~GObjRect(){}
};

#endif // GOBJRECT_H
