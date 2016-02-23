#ifndef GOBJ_H
#define GOBJ_H

#include <list>
#include <memory>
#include <vector>

#include "gtools.h"
#include "gpos.h"

class GContext;
class GWorldModel;

/// @brief Game object
/// @details Component in Composite.
/// @see GObj
class GObj : public GTools::enable_shared_from_this_virtual<GObj> {
public:
    typedef std::list<std::shared_ptr<GObj>> GObjPList;
    typedef std::shared_ptr<GObj> GObjP;
    typedef float DeltaT;

    explicit GObj(GPos = {0,0,0});
    virtual ~GObj(){}

    void removeChild(const GObjP &gObj);
    GObjP findChild(std::function<bool(const GObjP &)>) const;
    GObjPList findChilds(std::function<bool(const GObjP &)>, bool recursive = true) const;
    GObjPList findChilds(bool recursive = true) const;
    GObjPList findIntersectObjs(std::function<bool (const GObjP &)> check);
    GObjPList findIntersectObjs();
    virtual bool isIntersectWith(const GObjP &) const;

    inline const GObjP getParent() const {return parent.lock();}
    GObjP getRoot();

    GPos getPosAbsolute() const;
    inline GPos & getPos() {return pos;}
    inline void setPos(const GPos & pos) {this->pos = pos;}

    virtual void recalc(DeltaT, const GContext &) {}
    virtual void init() {}

    /// Add child. Returns pointer to added object casted to needed type.
    /// It is a template cuz ADD_CHILD macro hides only addChild method and can't affect
    /// on returning type this way "someGObj->ADD_CHILD(SomeGObjT)"
    template<typename TCastTo = GObj>
    std::shared_ptr<TCastTo> addChild(const GObjP & child) {
        child->setParent(shared_from_this());
        children.push_back(child);
        child->init();
        return std::dynamic_pointer_cast<TCastTo>(child);
    }

    class cant_find_child{};
    class no_valid_root{};

private:
    GPos pos;
    std::weak_ptr<GObj> parent;
    GObjPList children;

    void addChildsToListR(GObjPList &, std::function<bool(const std::shared_ptr<GObj> &)>, bool recursive = true) const;
    inline void setParent(const GObjP & parent) {this->parent = parent;}
};

#define ADD_CHILD(type,...)addChild<type>(std::make_shared<type>(__VA_ARGS__))
#define POS(x,y,z)(GPos({x,y,z}))

#endif // GOBJ_H
