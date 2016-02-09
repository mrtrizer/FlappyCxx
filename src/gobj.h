#ifndef GOBJ_H
#define GOBJ_H

#include <list>

class GWorld;

/// @brief Game object
/// @details Component in Composite.
/// @see GObjContainer
class GObj {
public:
    typedef std::list<GObj> GObjList;
    typedef std::list<const GObj *> GObjPList;
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

    inline Id getId() const {return id;}
    inline Pos & getPosR() {return pos;}

    inline bool operator == (const GObj & gObj) const {return gObj.getId() == getId();}

protected:
    inline void setWorld(const GWorld *) {this->gWorld = gWorld;}
    virtual GObjPList intersectObjList_() const;

private:
    const GWorld * gWorld = nullptr;
    Id id;
    Pos pos;
};

#endif // GOBJ_H
