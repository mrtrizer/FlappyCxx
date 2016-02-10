#ifndef GOBJCONTAINER_H
#define GOBJCONTAINER_H

#include "gobj.h"

///@brief Game Object Container
///@details Composite.
class GObjContainer : public GObj_CRTP<GObjContainer> {
    friend class GWorld;
public:
    explicit GObjContainer(Id);
    ~GObjContainer();
    ///Recursively
    GObjPList getChildsR() const;
    GObjPList getChilds() const;
    void addChild(const GObj&);
    void removeChild(Id);
    GObj *findChild(Id);
    GObj *findChildR(Id);

    class no_child_with_id_exception{};
    class obj_id_exists_exception{};

private:
    GObjPList children;

    ///Compiles tree to list
    void addChildsToListR(GObjPList &) const;
    GObjContainer(Id, GWorld *);
};

#endif // GOBJCONTAINER_H
