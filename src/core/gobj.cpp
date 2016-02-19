#include "gobj.h"
#include "tools.h"

GObj::GObj(Pos pos):pos(pos)
{

}

GObj::GObjPList GObj::intersectObjList() {
    GObjPList result;
    GObjPList allObjects = getRoot()->getChildsR();
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

/// Same as getChilds() but works recursively.
GObj::GObjPList GObj::getChildsR() {
    GObjPList objList;
    addChildsToListR(objList);
    return objList;
}

/// Returns a list of GObj childs.
GObj::GObjPList GObj::getChilds() const {
    GObjPList objList;
    for (auto i : children)
        objList.push_back(i);
    return objList;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChildR([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

//TODO: Return a list of appropriate objects
/// Search a child recursively using check callback for validation.
std::shared_ptr<GObj> GObj::findChildR(std::function<bool(const std::shared_ptr<GObj> &)> check) const {
    for (std::shared_ptr<GObj> i : children)
    {
        if (check(i))
            return i;
        auto container = std::dynamic_pointer_cast<GObj>(i);
        if (container != nullptr)
            try {
                return container->findChildR(check);
            } catch (cant_find_child &) {}
    }
    throw cant_find_child();
}

/// Compiles a tree to the list
/// @see getChildsR()
void GObj::addChildsToListR(GObjPList & list) {
    list.push_back(shared_from_this());
    for (std::shared_ptr<GObj> i : children) {
        std::shared_ptr<GObj> container = std::dynamic_pointer_cast<GObj>(i);
        if (container != nullptr)
            container->addChildsToListR(list);
        else
            list.push_back(i);
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
