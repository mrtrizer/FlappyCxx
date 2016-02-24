#include "gobj.h"
#include "gtools.h"

using namespace std;

GObj::GObj(GPos pos):pos(pos)
{

}

GObj::GObjPList GObj::findIntersectObjs(std::function<bool(const GObjP &)> check) {
    auto me = shared_from_this();
    return getRoot()->findChilds([me,check](const GObjP & obj){
        return (obj != me) && me->isIntersectWith(obj) && check(obj);
    });
}

GObj::GObjPList GObj::findIntersectObjs() {
    return findIntersectObjs([](const GObjP &){return true;});
}

bool GObj::isIntersectWith(const GObjP & gObj) const {
    return GTools::isIntersect(*this, *gObj);
}

GPos GObj::getPosAbsolute() const {
    if (getParent() != nullptr)
        return getParent()->getPosAbsolute() * this->pos;
    else
        return pos;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    gObj->getParent()->children.remove(gObj);
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

GObj::GObjPList GObj::findChilds(bool recursive) const {
    return findChilds([](const GObjP &){return true;}, recursive);
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
