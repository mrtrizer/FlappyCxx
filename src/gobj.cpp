#include "gobj.h"
#include "tools.h"

GObj::GObj(Id id, Pos pos):id(id),pos(pos)
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

bool GObj::isIntersectWith(const GObj & gObj) const {
    return Tools::isIntersect(*this, gObj);
}
