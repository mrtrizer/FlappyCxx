#include "gpos.h"

const GPos & GPos::operator* (const GPos & pos) {
    x += pos.x;
    y += pos.y;
    z += pos.z;
    return *this;
}

void GPos::move(const GPos & offset) {
    this->setX(this->getX() + offset.getX());
    this->setY(this->getY() + offset.getY());
    this->setZ(this->getZ() + offset.getZ());
}

GPos::MvMatrix GPos::getMvMatrix() const {
    return MvMatrix({
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, 1.0f, 0,
        getX(), getY(), getZ(), 1.0f
    });
}
