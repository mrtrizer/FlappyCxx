#include <typeinfo>

#include "gobjcircle.h"

GObjCircle::GObjCircle(R r, Pos pos):
    GObj(pos),
    GColliderCircle(r),
    GViewCircle(5)
{

}
