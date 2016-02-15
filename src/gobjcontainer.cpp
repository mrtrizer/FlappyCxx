#include <typeinfo>

#include "gobjcontainer.h"

GObjContainer::GObjContainer(Id id): GObj_CRTP<GObjContainer>(id)
{

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

GObj::Id GObjContainer::addChild(const GObj & child) {
    const GObjContainer * root = getRoot();
    try {
        root->findChildR(child.getId());
        throw obj_id_exists_exception();
    } catch (no_child_with_id_exception &) { //no objects with same id
        GObj * objClone = child.clone(child.getId(),this);
        children.push_back(objClone);
    }
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
