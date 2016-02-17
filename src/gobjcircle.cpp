#include <typeinfo>

#include "gobjcircle.h"

GObjCircle::GObjCircle(R r, Pos pos):
    GObj(pos),
    GColliderCircle(r),
    GViewCustom(25)
{

}
