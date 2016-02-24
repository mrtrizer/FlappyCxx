#ifndef GDECOR_H
#define GDECOR_H

#include <string>

#include "core/gobj.h"
#include "core/gpresenter.h"
#include "core/gcollider.h"

class GDecor: public GObj, public GColliderRect, public GPresenterSprite {
public:
    GDecor(std::string path, float width, float height, GPos pos = {0,0,0}):
        GObj(pos),
        GColliderRect(width, height),
        GPresenterSprite(path,width,height)
    {}
};

#endif // GDECOR_H
