#include "gobj.h"

GObj::GObj(Id id):id(id)
{

}

GObj::GObjPList GObj::intersectObjList() const {
    if (gWorld == nullptr)
        return GObjPList();
    return intersectObjList_();
}

GObj::GObjPList GObj::intersectObjList_() const {
    return GObjPList();
}

bool GObj::isIntersectWith(const GObj &) const {
    return false;
}
