#ifndef GOBJCAMERA_H
#define GOBJCAMERA_H

#include "gobj.h"

class GObjCamera : public GObj
{
public:
    typedef float Height;

    GObjCamera(Height,Pos);
    Height getHeight() { return height; }

private:
    Height height;

};

#endif // GOBJCAMERA_H
