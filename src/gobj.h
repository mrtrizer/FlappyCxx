#ifndef GOBJ_H
#define GOBJ_H

#include <list>
#include <memory>

class GWorld;
class GObjContainer;

/// @brief Game object
/// @details Component in Composite.
/// @see GObjContainer
class GObj {
    friend class GObjContainer; //calls setParent()
public:
    typedef std::list<std::shared_ptr<GObj>> GObjPList;
    typedef std::shared_ptr<GObjContainer> GObjContainerP;
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

    GObjPList intersectObjList() const;
    virtual bool isIntersectWith(const GObj &) const;
    std::shared_ptr<GObjContainer> getRoot() const;

    Pos getPosAbsolute() const;
    inline Pos & getPosR() {return pos;}
    inline const Pos & getPos() const {return pos;}
    inline void setPos(const Pos & pos) {this->pos = pos;}
    inline const GObjContainerP getParent() const {return parent.lock();}
    virtual void recalc(DeltaT) {}

    class no_valid_root{};

protected:
    virtual GObjPList intersectObjList_() const;

private:
    Pos pos;
    std::weak_ptr<GObjContainer> parent;

    inline void setParent(std::shared_ptr<GObjContainer> parent) {this->parent = parent;}
};

#endif // GOBJ_H
