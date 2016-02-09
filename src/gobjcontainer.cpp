#include <typeinfo>

#include "gobjcontainer.h"

GObjContainer::GObjContainer(Id id): GObj(id)
{

}

GObjContainer::GObjContainer(Id id, GWorld * gWorld): GObj(id)
{
    setWorld(gWorld);
}

GObj::GObjPList GObjContainer::getChildsR() const {
    GObjPList objList;
    addChildsToListR(objList);
    return objList;
}

GObj::GObjPList GObjContainer::getChilds() const {
    GObjPList objList;
    for (const GObj & i : children)
        objList.push_back(&i);
    return objList;
}

void GObjContainer::addChild(const GObj & child) {
    children.push_back(child);
}

void GObjContainer::removeChild(Id id) {
    for (const GObj & i : children)
        if (i.getId() == id)
            children.remove(i);
}

const GObj & GObjContainer::getChild(Id id) const {
    for (const GObj & i : children)
        if (i.getId() == id)
            return i;
    throw no_child_with_id_exception();
}

void GObjContainer::addChildsToListR(GObjPList & list) const {
    for (const GObj & i : children) {
        if (typeid(i) == typeid(GObjContainer))
            addChildsToListR(list);
        else
            list.push_back(&i);
    }
}
