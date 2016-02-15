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

GObj::Id GObjContainer::getNextId() {
    if (getParent() == nullptr)
        return ++lastId;
    else
        return lastId;
}

GObj::Id GObjContainer::addChild(const GObj & child) {
    const GObjContainer * root = getRoot();
    GObj * objClone = child.clone(getNextId(),this);
    children.push_back(objClone);
    return objClone->getId();
}

void GObjContainer::removeChild(Id id) {
    children.remove(findChild(id));
}

GObj * GObjContainer::findChild(Id id) const {
    for (GObj * i : children)
        if (i->getId() == id)
            return i;
    throw no_child_with_id_exception();
}

GObj * GObjContainer::findChildR(Id id) const {
    for (GObj * i : children)
    {
        if (i->getId() == id)
            return i;
        GObjContainer * container = dynamic_cast<GObjContainer *>(i);
        if (container != nullptr)
            try {
                return container->findChildR(id);
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
