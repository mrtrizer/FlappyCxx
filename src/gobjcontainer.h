#ifndef GOBJCONTAINER_H
#define GOBJCONTAINER_H

#include <functional>
#include <memory>

#include "gobj.h"

///@brief Game Object Container
///@details Composite.
class GObjContainer : public std::enable_shared_from_this<GObjContainer>, public GObj {
public:
    explicit GObjContainer(Pos = {0,0,0});
    ~GObjContainer();
    ///Recursively
    GObjPList getChildsR() const;
    GObjPList getChilds() const;
    template<typename TCastTo = GObj>
    std::shared_ptr<TCastTo> addChild(const std::shared_ptr<GObj> & child) {
        child->setParent(shared_from_this());
        children.push_back(child);
        return std::dynamic_pointer_cast<TCastTo>(child);
    }
    void removeChild(const std::shared_ptr<GObj> &gObj);
    std::shared_ptr<GObj> findChildR(std::function<bool(const std::shared_ptr<GObj> &)>) const;
    std::shared_ptr<GObjContainer> getRoot();

    class no_child_with_id_exception{};
    class obj_id_exists_exception{};

private:
    GObjPList children;

    ///Compiles tree to list
    void addChildsToListR(GObjPList &) const;
};

#endif // GOBJCONTAINER_H
