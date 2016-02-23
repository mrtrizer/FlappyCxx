#ifndef GOBJCAMERA_H
#define GOBJCAMERA_H

#include "gobj.h"
#include "gtools.h"
#include "gobjpointer.h"

/// @brief Game camera. Contains screen parameters.
/// A camera can be set as active in GWordCtrl and used by View
/// to get a perspective transformation matrix. Also camera
/// manages coordinates of GObjPointer object.
class GObjCamera : public GObj
{
public:
    typedef float Size;
    typedef float Ratio;
    typedef int WindowHeight;
    typedef std::vector<float> PMatrix;
    typedef std::shared_ptr<GObjPointer> GObjPointerP;

    struct Rect {
        float x1;
        float y1;
        float x2;
        float y2;
    };

    GObjCamera(Size, Ratio, WindowHeight windowHeight, GPos);
    void resize(double width, double height);
    Rect getRect() const;
    virtual PMatrix getPMatrix() const;
    void init() override final;
    void recalc(DeltaT, const GContext &);

private:
    /// Height in game units
    Size height;
    /// RealWidth(px) / RealHeight(px)
    Ratio ratio;
    /// RealHeight(px) / height(units)
    float coeff;
    GObjPointerP gObjPointer;

};

#endif // GOBJCAMERA_H
