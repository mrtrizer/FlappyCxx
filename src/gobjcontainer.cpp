#include <typeinfo>
#include <stdexcept>

#include "gobjcontainer.h"

GObjContainer::GObjContainer(): GObj_CRTP<GObjContainer>() {

}

GObjContainer::GObjContainer(const GObjContainer & gObjContainer) {
    if (gObjContainer.getChilds().size() != 0)
        throw std::runtime_error("Copy constructor for GObjContainer with childs isn't implemented!");
}

GObjContainer::~GObjContainer() {
    for (GObj * i: children)
        delete i;
}

GObj::GObjPList GObjContainer::getChildsR() const {
    GObjPList objList;
    addChildsToListR(objList);
    return objList;
}

GObj::GObjPList GObjContainer::getChilds() const {
    GObjPList objList;
    for (GObj * i : children)
        objList.push_back(i);
    return objList;
}

GObj *GObjContainer::addChild(const GObj & child) {
    GObj * objClone = child.clone(this);
    children.push_back(objClone);
    return objClone;
}

void GObjContainer::removeChild(GObj * gObj) {
    children.remove(findChildR([gObj](GObj * gObj){return gObj == gObj;}));
    delete gObj;
}

GObj * GObjContainer::findChild(std::function<bool(GObj *)> check) const {
    for (GObj * i : children)
        if (check(i))
            return i;
    throw no_child_with_id_exception();
}

GObj * GObjContainer::findChildR(std::function<bool(GObj*)> check) const {
    for (GObj * i : children)
    {
        if (check(i))
            return i;
        GObjContainer * container = dynamic_cast<GObjContainer *>(i);
        if (container != nullptr)
            try {
                return container->findChildR(check);
            } catch (no_child_with_id_exception &) {}
    }
    throw no_child_with_id_exception();
}

void GObjContainer::addChildsToListR(GObjPList & list) const {
    for (GObj * i : children) {
        GObjContainer * container = dynamic_cast<GObjContainer *>(i);
        if (container != nullptr)
            container->addChildsToListR(list);
        else
            list.push_back(i);
    }
}
