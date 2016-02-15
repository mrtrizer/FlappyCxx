#include <typeinfo>
#include <stdexcept>

#include "gobjcontainer.h"

GObjContainer::GObjContainer(Pos pos): GObj(pos) {

}

GObjContainer::~GObjContainer() {
}

GObj::GObjPList GObjContainer::getChildsR() const {
    GObjPList objList;
    addChildsToListR(objList);
    return objList;
}

GObj::GObjPList GObjContainer::getChilds() const {
    GObjPList objList;
    for (std::shared_ptr<GObj> i : children)
        objList.push_back(i);
    return objList;
}

void GObjContainer::removeChild(const std::shared_ptr<GObj> & gObj) {
    children.remove(findChildR([gObj](const std::shared_ptr<GObj> & i){return i == gObj;}));
}

std::shared_ptr<GObj> GObjContainer::findChildR(std::function<bool(const std::shared_ptr<GObj> &)> check) const {
    for (std::shared_ptr<GObj> i : children)
    {
        if (check(i))
            return i;
        std::shared_ptr<GObjContainer> container = std::dynamic_pointer_cast<GObjContainer>(i);
        if (container != nullptr)
            try {
                return container->findChildR(check);
            } catch (no_child_with_id_exception &) {}
    }
    throw no_child_with_id_exception();
}

void GObjContainer::addChildsToListR(GObjPList & list) const {
    for (std::shared_ptr<GObj> i : children) {
        std::shared_ptr<GObjContainer> container = std::dynamic_pointer_cast<GObjContainer>(i);
        if (container != nullptr)
            container->addChildsToListR(list);
        else
            list.push_back(i);
    }
}

std::shared_ptr<GObjContainer> GObjContainer::getRoot() {
    const std::shared_ptr<GObj> root = getParent();
    if (root == nullptr)
        return shared_from_this();
    else
        return root->getParent();
}

