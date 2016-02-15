#ifndef GOBJCONTAINER_H
#define GOBJCONTAINER_H

#include "gobj.h"

///@brief Game Object Container
///@details Composite.
class GObjContainer : public GObj_CRTP<GObjContainer> {
public:
    explicit GObjContainer();
    GObjContainer(const GObjContainer &);
    ~GObjContainer();
    ///Recursively
    GObjPList getChildsR() const;
    GObjPList getChilds() const;
    GObj::Id addChild(const GObj&);
    void removeChild(Id);
    GObj *findChild(Id) const;
    GObj *findChildR(Id) const;
    //TODO: Implement kinda GObjIdController to dispose of lastId in every GObjContainer.
    Id getNextId();

    class no_child_with_id_exception{};
    class obj_id_exists_exception{};

private:
    GObjPList children;
    Id lastId = 0;

    ///Compiles tree to list
    void addChildsToListR(GObjPList &) const;
};

#endif // GOBJCONTAINER_H
