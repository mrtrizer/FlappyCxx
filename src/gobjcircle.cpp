#include <typeinfo>

#include "gobjcircle.h"

GObjCircle::GObjCircle(Id id, R r, Pos pos):
    GObj_CRTP<GObjCircle>(id, pos),
    r(r)
{

}
