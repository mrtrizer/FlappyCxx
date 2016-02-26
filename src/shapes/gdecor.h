#ifndef GDECOR_H
#define GDECOR_H

#include <string>

#include "core/gobj.h"
#include "core/gpresenter.h"
#include "core/gcollider.h"

/// GDecor in fact just allows put a GPresenterSprite to an object tree.
class GDecor: public GObj, public GPresenterSprite {
public:
    GDecor(std::string path, float width, float height, GPos pos = {0,0,0}, int frameCnt = 1):
        GObj(pos),
        GPresenterSprite(path,width,height,frameCnt)
    {}
};

#endif // GDECOR_H
