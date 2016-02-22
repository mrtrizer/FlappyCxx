#ifndef GOBJPOINTER_H
#define GOBJPOINTER_H

#include "gobj.h"
#include "gcollider.h"
#include "gviewshape.h"

class GObjPointer: GObj, GColliderCircle, GViewCircle {
public:
    GObjPointer(int x, int y, MouseEvent mouseEvent):
        GObj(GPos(x,y,0)),
        GColliderCircle(1),
        GViewCircle(10,1)
    {}
    inline GContext getContext() {return context;}
private:
    GContext context;
};

#endif // GOBJPOINTER_H
