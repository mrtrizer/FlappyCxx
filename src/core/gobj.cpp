#include "gobj.h"
#include "tools.h"

GObj::GObj(Pos pos):pos(pos)
{

}

GObj::GObjPList GObj::intersectObjList() {
    auto me = shared_from_this();
    return getRoot()->findChilds([me](const GObjP & obj){
        return (obj != me) && me->isIntersectWith(obj);
    });
}

bool GObj::isIntersectWith(const GObjP & gObj) const {
    return Tools::isIntersect(*this, *gObj);
}

GObj::Pos GObj::getPosAbsolute() const {
    if (getParent() != nullptr)
        return getParent()->getPosAbsolute() + this->pos;
    else
        return pos;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChild([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

/// Search a child recursively using check callback for validation.
std::shared_ptr<GObj> GObj::findChild(std::function<bool(const GObjP &)> check) const {
    GObjPList objList = findChilds(check);
    if (objList.size() == 0)
        throw cant_find_child();
    return objList.back();
}

GObj::GObjPList GObj::findChilds(std::function<bool(const GObjP &)> check, bool recursive) const {
    GObjPList objList;
    addChildsToListR(objList, check, recursive);
    return objList;
}

/// Compiles a tree to the list
/// @see getChildsR()
void GObj::addChildsToListR(GObjPList & list, std::function<bool(const std::shared_ptr<GObj> &)> check, bool recursive) const {
    for (std::shared_ptr<GObj> i : children) {
        if (check(i))
            list.push_back(i);
        if (recursive)
            i->addChildsToListR(list, check);
    }
}

/// Recursive ups to the root and returns it.
std::shared_ptr<GObj> GObj::getRoot() {
    const std::shared_ptr<GObj> root = getParent();
    if (root == nullptr)
        return shared_from_this();
    else
        return root->getRoot();
}

const GObj::Pos & GObj::Pos::operator+ (const Pos & pos) {
    x += pos.x;
    y += pos.y;
    z += pos.z;
    return *this;
}
