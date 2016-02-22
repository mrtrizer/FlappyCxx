#include "gobjcamera.h"

GObjCamera::GObjCamera(Size height, Ratio ratio, WindowHeight windowHeight, GPos pos):
    GObj(pos),
    height(height),
    ratio(ratio),
    coeff(height / windowHeight) {
}

Tools::Rect GObjCamera::getRect() const {
    GPos pos = getPosAbsolute();
    float offset = height / 2;
    return {
        -offset * ratio - pos.getX(),
        offset - pos.getY(),
        offset * ratio - pos.getX(),
        -offset - pos.getY(),
    };
}

void GObjCamera::resize(double width, double height) {
    this->ratio = width / height;
    this->coeff = this->height / height;
}

GObjCamera::PMatrix GObjCamera::getPMatrix() const {
    auto rect = getRect();
    static const float near = -1.0f;
    static const float far = 99.0f;

    return PMatrix({
           2.0f / (rect.x2 - rect.x1), 0, 0, 0,
           0, 2.0f / (rect.y1 - rect.y2), 0, 0,
           0, 0, -2.0f / (far - near), 0,
           (rect.x2 + rect.x1) / (rect.x2 - rect.x1), (rect.y1 + rect.y2) / (rect.y1 - rect.y2), (far + near) / (far - near), 1.0f
    });
}
