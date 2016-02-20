#include "gobj.h"
#include "tools.h"

using namespace std;

GObj::GObj(GPos pos):pos(pos)
{

}

GObj::GObjPList GObj::findIntersectObjs() {
    auto me = shared_from_this();
    return getRoot()->findChilds([me](const GObjP & obj){
        return (obj != me) && me->isIntersectWith(obj);
    });
}

bool GObj::isIntersectWith(const GObjP & gObj) const {
    return Tools::isIntersect(*this, *gObj);
}

GPos GObj::getPosAbsolute() const {
    if (getParent() != nullptr)
        return getParent()->getPosAbsolute() * this->pos;
    else
        return pos;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChild([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

/// Search a child recursively using check callback for validation.
GObj::GObjP GObj::findChild(std::function<bool(const GObjP &)> check) const {
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
void GObj::addChildsToListR(GObjPList & list, std::function<bool(const GObjP &)> check, bool recursive) const {
    for (std::shared_ptr<GObj> i : children) {
        if (check(i))
            list.push_back(i);
        if (recursive)
            i->addChildsToListR(list, check);
    }
}

/// Recursive ups to the root and returns it.
GObj::GObjP GObj::getRoot() {
    const std::shared_ptr<GObj> root = getParent();
    if (root == nullptr)
        return shared_from_this();
    else
        return root->getRoot();
}
