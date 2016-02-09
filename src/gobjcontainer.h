#ifndef GOBJCONTAINER_H
#define GOBJCONTAINER_H

#include "gobj.h"

///@brief Game Object Container
///@details Composite.
class GObjContainer : public GObj
{
    friend class GWorld;
public:
    explicit GObjContainer(Id);
    ///Recursively
    GObjPList getChildsR() const;
    GObjPList getChilds() const;
    void addChild(const GObj&);
    void removeChild(Id);
    const GObj & getChild(Id) const;

    class no_child_with_id_exception{};

private:
    GObjList children;

    ///Compiles tree to list
    void addChildsToListR(GObjPList &) const;
    GObjContainer(Id, GWorld *);
};

#endif // GOBJCONTAINER_H
