#ifndef GCOLLIDER_H
#define GCOLLIDER_H

#include "tools.h"

/// Contains shape properties of an object.
/// All objects implementing intersection processing has to be inherited from it.
/// See intersection finding in the Tools namespace.
class GCollider : public Tools::enable_shared_from_this_virtual<GCollider> {
public:
    GCollider();
    virtual ~GCollider(){}
};

class GColliderCircle: public GCollider {
public:
    typedef float R;

    explicit GColliderCircle(R r = 0):r(r){}
    inline void setR(R r) {this->r = r;}
    inline R getR() const {return r;}

private:
    R r = 0;
};

class GColliderRect: public GCollider {
public:
    typedef float Size;

    explicit GColliderRect(Size width, Size height):width(width), height(height) {}
    inline Size getWidth() const {return width;}
    inline Size getHeight() const {return height;}
    inline void setWidth(Size width) {this->width = width;}
    inline void setHeight(Size height) {this->height = height;}
private:
    Size width;
    Size height;
};

#endif // GCOLLIDER_H
