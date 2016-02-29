#ifndef FLOOR_H
#define FLOOR_H

#include "core/gobj.h"
#include "core/gcollider.h"

class Floor : public GColliderRect
{
public:
    Floor(float width, GPos pos);
};

#endif // FLOOR_H
