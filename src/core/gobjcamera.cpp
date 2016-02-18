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
        -offset * ratio - pos.x,
        offset - pos.y,
        offset * ratio - pos.x,
        -offset - pos.y,
    };
}
