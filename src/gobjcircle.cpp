#include <typeinfo>

#include "gobjcircle.h"

GObjCircle::GObjCircle(R r, Pos pos):
    GObj_CRTP<GObjCircle>(pos),
    r(r)
{

}
