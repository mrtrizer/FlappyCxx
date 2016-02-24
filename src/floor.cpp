#include "floor.h"

Floor::Floor(float width, GPos pos) :
    GObj(pos),
    GColliderRect(width, 10)
{}
