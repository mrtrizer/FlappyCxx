#include "gobj.h"
#include "tools.h"

GObj::GObj(Pos pos):pos(pos)
{

}

GObj::GObjPList GObj::intersectObjList() {
    GObjPList result;
    GObjPList allObjects = getRoot()->findChildsR();
    auto me = shared_from_this();
    for (auto i: allObjects) {
        if (i != me) {
            if (i->isIntersectWith(me))
                result.push_back(i);
        }
    }
    return result;
}

bool GObj::isIntersectWith(const GObjP & gObj) const {
    return Tools::isIntersect(*this, *gObj);
}

GObj::Pos GObj::getPosAbsolute() const {
    if (getParent() != nullptr) {
        return getParent()->getPosAbsolute() + this->pos;
    }
    else
        return pos;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChildR([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

//TODO: Return a list of appropriate objects
/// Search a child recursively using check callback for validation.
std::shared_ptr<GObj> GObj::findChildR(std::function<bool(const GObjP &)> check) const {
    GObjPList objList;
    addChildsToListR(objList,check);
    if (objList.size() == 0)
        throw cant_find_child();
    return objList.back();
}

GObj::GObjPList GObj::findChildsR(std::function<bool(const GObjP &)> check, bool recursive) const {
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
