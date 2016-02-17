#ifndef GOBJ_H
#define GOBJ_H

#include <list>
#include <memory>

#include "tools.h"

class GWorldModel;

/// @brief Game object
/// @details Component in Composite.
/// @see GObj
class GObj : public Tools::enable_shared_from_this_virtual<GObj> {
public:
    typedef std::list<std::shared_ptr<GObj>> GObjPList;
    typedef std::shared_ptr<GObj> GObjP;
    typedef int DeltaT;

    struct Pos {
        const Pos & operator+ (const Pos & pos);
        float x;
        float y;
        float z;
    };

    explicit GObj(Pos = {0,0,0});
    virtual ~GObj(){}

    GObjPList intersectObjList();
    virtual bool isIntersectWith(const GObjP &) const;
    std::shared_ptr<GObj> getRoot() const;

    Pos getPosAbsolute() const;
    inline Pos & getPosR() {return pos;}
    inline const Pos & getPos() const {return pos;}
    inline void setPos(const Pos & pos) {this->pos = pos;}
    inline const GObjP getParent() const {return parent.lock();}
    virtual void recalc(DeltaT) {}

    GObjPList getChildsR();
    GObjPList getChilds() const;
    /// Add child. Returns pointer to added object casted to needed type.
    template<typename TCastTo = GObj>
    std::shared_ptr<TCastTo> addChild(const std::shared_ptr<GObj> & child) {
        child->setParent(shared_from_this_cast());
        children.push_back(child);
        return std::dynamic_pointer_cast<TCastTo>(child);
    }
    void removeChild(const std::shared_ptr<GObj> &gObj);
    std::shared_ptr<GObj> findChildR(std::function<bool(const std::shared_ptr<GObj> &)>) const;
    std::shared_ptr<GObj> getRoot();

    class cant_find_child{};
    class no_valid_root{};

private:
    Pos pos;
    std::weak_ptr<GObj> parent;
    GObjPList children;

    void addChildsToListR(GObjPList &);
    inline void setParent(std::shared_ptr<GObj> parent) {this->parent = parent;}
};

#endif // GOBJ_H
