#include "gobj.h"
#include "tools.h"

GObj::GObj(Pos pos):pos(pos)
{

}

GObj::GObjPList GObj::intersectObjList() {
    GObjPList gObjPList;
    auto me = shared_from_this_cast();
    for (auto i: getChildsR()) {
        if (i != me) {
            if (i->isIntersectWith(me))
                gObjPList.push_back(i);
        }
    }
    return gObjPList;
}

bool GObj::isIntersectWith(const GObjP & gObj) const {
    return Tools::isIntersect(*this, *gObj);
}

std::shared_ptr<GObj> GObj::getRoot() const {
    throw no_valid_root();
}

GObj::Pos GObj::getPosAbsolute() const {
    if (getParent() != nullptr) {
        return getParent()->getPosAbsolute() + this->pos;
    }
    else
        return pos;
}

GObj::GObjPList GObj::getChildsR() {
    GObjPList objList;
    addChildsToListR(objList);
    return objList;
}

GObj::GObjPList GObj::getChilds() const {
    GObjPList objList;
    for (auto i : children)
        objList.push_back(i);
    return objList;
}

void GObj::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChildR([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

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

void GObj::addChildsToListR(GObjPList & list) {
    list.push_back(shared_from_this_cast());
    for (std::shared_ptr<GObj> i : children) {
        std::shared_ptr<GObj> container = std::dynamic_pointer_cast<GObj>(i);
        if (container != nullptr)
            container->addChildsToListR(list);
        else
            list.push_back(i);
    }
}

std::shared_ptr<GObj> GObj::getRoot() {
    const std::shared_ptr<GObj> root = getParent();
    if (root == nullptr)
        return shared_from_this_cast();
    else
        return root->getParent();
}

const GObj::Pos & GObj::Pos::operator+ (const Pos & pos) {
    x += pos.x;
    y += pos.y;
    z += pos.z;
    return *this;
}
