#include "gobjcamera.h"

GObjCamera::GObjCamera(Size height, Ratio ratio, Pos pos):
    GObj(pos),
    height(height),
    ratio(ratio) {
}

Tools::Rect GObjCamera::getRect() const {
    GObj::Pos pos = getPosAbsolute();
    float offset = height / 2;
    return {
        -offset * ratio - pos.getX(),
        offset - pos.getY(),
        offset * ratio - pos.getX(),
        -offset - pos.getY(),
    };
}
