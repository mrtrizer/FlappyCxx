#ifndef GOBJ_H
#define GOBJ_H

#include <list>

class GWorld;
class GObjContainer;

/// @brief Game object
/// @details Component in Composite.
/// @see GObjContainer
class GObj {
    friend class GObjContainer;
public:
    typedef std::list<GObj *> GObjPList;
    typedef unsigned int Id;
    struct Pos {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    explicit GObj(Id);
    virtual ~GObj(){}

    /// Returns a list of pointers to objects intersects with. Add object to a world, before use.
    GObjPList intersectObjList() const;
    virtual bool isIntersectWith(const GObj &) const;
    virtual GObj* clone() const = 0;

    inline Id getId() const {return id;}
    inline Pos & getPosR() {return pos;}
    inline GObjContainer * getParent() {return parent;}
    inline const GWorld * getWorld() {return gWorld;}

    inline bool operator == (const GObj & gObj) const {return gObj.getId() == getId();}

protected:
    inline void setWorld(const GWorld * gWorld) {this->gWorld = gWorld;}
    inline void setParent(GObjContainer * parent) {this->parent = parent;}
    virtual GObjPList intersectObjList_() const;

private:
    const GWorld * gWorld = nullptr;
    Id id;
    Pos pos;
    GObjContainer * parent = nullptr;
};

/// @brief Curiously recurring template pattern (CRTP)
/// @details Avoids copy&past of clone method.
template <typename Derived, typename From = GObj> class GObj_CRTP: public From {
public:
    GObj_CRTP<Derived, From>(GObj::Id id):From(id)
    {}

    GObj* clone() const {
        return new Derived(dynamic_cast<Derived const&>(*this));
    }
};

#endif // GOBJ_H
