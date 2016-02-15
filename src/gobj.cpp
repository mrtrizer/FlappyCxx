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
    //TODO: Implement me
    return GObjPList();
}

bool GObj::isIntersectWith(const GObj & gObj) const {
    return Tools::isIntersect(*this, gObj);
}

std::shared_ptr<GObjContainer> GObj::getRoot() const {
    throw no_valid_root();
}

GObj::Pos GObj::getPosAbsolute() const {
    if (getParent() != nullptr) {
        return getParent()->getPosAbsolute() + this->pos;
    }
    else
        return pos;
}

const GObj::Pos & GObj::Pos::operator+ (const Pos & pos) {
    x += pos.x;
    y += pos.y;
    z += pos.z;
    return *this;
}
