#include "gobj.h"
#include "tools.h"
#include "gobjcontainer.h"

GObj::GObj(Pos pos):pos(pos)
{

}

GObj::GObjPList GObj::intersectObjList() const {
    if (getParent() == nullptr)
        return GObjPList();
    return intersectObjList_();
}

GObj::GObjPList GObj::intersectObjList_() const {
    return GObjPList();
}

bool GObj::isIntersectWith(const GObj & gObj) const {
    return Tools::isIntersect(*this, gObj);
}

const GObjContainer * GObj::getRoot() const {
    const GObj * root = this;
    while (root->getParent() != nullptr)
        root = root->getParent();
    return dynamic_cast<const GObjContainer*>(root);
}
