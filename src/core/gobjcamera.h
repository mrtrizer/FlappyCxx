#ifndef GOBJCAMERA_H
#define GOBJCAMERA_H

#include "gobj.h"
#include "tools.h"
#include "gobjpointer.h"


class GObjCamera : public GObj
{
public:
    typedef float Size;
    typedef float Ratio;
    typedef int WindowHeight;
    typedef std::vector<float> PMatrix;
    typedef std::shared_ptr<GObjPointer> GObjPointerP;

    GObjCamera(Size, Ratio, WindowHeight windowHeight, GPos);
    inline Size getHeight() const { return height; }
    void resize(double width, double height);
    Tools::Rect getRect() const;
    virtual PMatrix getPMatrix() const;
    void init() override final;
    void recalc(DeltaT, GContext context);

private:
    Size height;
    Ratio ratio;
    float coeff;
    GObjPointerP gObjPointer;

};

#endif // GOBJCAMERA_H
