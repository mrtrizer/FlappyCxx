#ifndef GOBJCAMERA_H
#define GOBJCAMERA_H

#include "gobj.h"
#include "tools.h"

class GObjCamera : public GObj
{
public:
    typedef float Size;
    typedef float Ratio;

    GObjCamera(Size,Ratio,Pos);
    inline Size getHeight() const { return height; }
    inline void setRatio(Ratio ratio) {this->ratio = ratio;}
    Tools::Rect getRect() const;

private:
    Size height;
    Ratio ratio;

};

#endif // GOBJCAMERA_H
