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
    struct Pos {
        double x;
        double y;
        double z;
    };

    explicit GObj(Pos = {0,0,0});
    virtual ~GObj(){}

    /// Returns a list of pointers to objects intersects with. Add object to a world, before use.
    GObjPList intersectObjList() const;
    virtual bool isIntersectWith(const GObj &) const;
    virtual GObj* clone(GObjContainer * parent) const = 0;
    const GObjContainer *getRoot() const;

    inline Pos & getPosR() {return pos;}
    inline const Pos & getPos() const {return pos;}
    inline void setPos(const Pos & pos) {this->pos = pos;}
    inline const GObjContainer * getParent() const {return parent;}
    //TODO: IMPLEMENT ME
    inline bool operator == (const GObj & gObj) const {}
    inline void setParent(GObjContainer * parent) {this->parent = parent;}

protected:
    virtual GObjPList intersectObjList_() const;

private:
    Pos pos;
    GObjContainer * parent = nullptr;
};

/// @brief Divno-rekursivny pattern (CRTP)
/// @details Avoids copy&past of a clone method.
template <typename Derived, typename From = GObj> class GObj_CRTP: public From {
public:
    using From::From; //to not duplicate a constructor

    virtual GObj* clone(GObjContainer * parent) const override {
        GObj * clone = new Derived(dynamic_cast<Derived const&>(*this));
        clone->setParent(parent);
        return clone;
    }
};

#endif // GOBJ_H
