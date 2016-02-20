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
    typedef float DeltaT;

    class Pos {
    public:
        Pos(float x, float y, float z):
            x(x),y(y),z(z){}
        virtual const Pos & operator* (const Pos & pos);
        virtual void move(const Pos &);
        inline void setX(float x) {this->x = x;}
        inline void setY(float y) {this->y = y;}
        inline void setZ(float z) {this->z = z;}
        inline float getX() const {return this->x;}
        inline float getY() const {return this->y;}
        inline float getZ() const {return this->z;}

    private:
        float x;
        float y;
        float z;
    };

    explicit GObj(Pos = {0,0,0});
    virtual ~GObj(){}

    GObjPList findIntersectObjs();
    virtual bool isIntersectWith(const GObjP &) const;
    std::shared_ptr<GObj> getRoot() const;

    Pos getPosAbsolute() const;
    inline Pos & getPos() {return pos;}
    inline void setPos(const Pos & pos) {this->pos = pos;}
    inline const GObjP getParent() const {return parent.lock();}
    virtual void recalc(DeltaT) {}
    virtual void init() {}

    /// Add child. Returns pointer to added object casted to needed type.
    template<typename TCastTo = GObj>
    std::shared_ptr<TCastTo> addChild(const GObjP & child) {
        child->setParent(shared_from_this());
        children.push_back(child);
        child->init();
        return std::dynamic_pointer_cast<TCastTo>(child);
    }
    void removeChild(const GObjP &gObj);
    GObjP findChild(std::function<bool(const GObjP &)>) const;
    GObjPList findChilds(std::function<bool(const GObjP &)>, bool recursive = true) const;
    GObjPList findChilds(bool recursive = true) const {
        return findChilds([](const GObjP &){return true;}, recursive);
    }

    GObjP getRoot();

    class cant_find_child{};
    class no_valid_root{};

private:
    Pos pos;
    std::weak_ptr<GObj> parent;
    GObjPList children;

    void addChildsToListR(GObjPList &, std::function<bool(const std::shared_ptr<GObj> &)>, bool recursive = true) const;
    inline void setParent(const GObjP & parent) {this->parent = parent;}
};

#define ADD_CHILD(type,...)addChild<type>(std::make_shared<type>(__VA_ARGS__))
#define POS(x,y,z)(GObj::Pos({x,y,z}))

#endif // GOBJ_H
