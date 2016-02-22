#ifndef GOBJPOINTER_H
#define GOBJPOINTER_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjPointer: public GObj, public GColliderCircle, public GViewCircle {
    friend class GObjCamera;
public:
    GObjPointer():
        GObj(GPos(0,0,0)),
        GColliderCircle(0.1),
        GViewCircle(10,0.1)
    {}
    inline GContext getContext() {return context;}

private:
    GContext context;
};

#endif // GOBJPOINTER_H
