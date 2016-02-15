#ifndef GOBJCONTAINER_H
#define GOBJCONTAINER_H

#include <functional>

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
    GObj *addChild(const GObj&);
    void removeChild(GObj *gObj);
    GObj *findChild(std::function<bool(GObj*)>) const;
    GObj *findChildR(std::function<bool(GObj *)>) const;

    class no_child_with_id_exception{};
    class obj_id_exists_exception{};

private:
    GObjPList children;

    ///Compiles tree to list
    void addChildsToListR(GObjPList &) const;
};

#endif // GOBJCONTAINER_H
