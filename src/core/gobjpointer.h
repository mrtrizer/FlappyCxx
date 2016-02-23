#ifndef GOBJPOINTER_H
#define GOBJPOINTER_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

/// Mouse pointer in a game world. It is created and managerd by
/// GObjCamera, because it knows about screen parameters.
class GObjPointer: public GObj, public GColliderCircle {
public:
    GObjPointer():
        GObj(GPos(0,0,0)),
        GColliderCircle(0.1)
    {}
};

#endif // GOBJPOINTER_H
