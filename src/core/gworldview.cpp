#include "gworldview.h"
#include "gobjcamera.h"
#include "gworldmodel.h"

void GWorldView::setGWorldModel(GWorldModelP gWorldModel) {
    this->gWorld = gWorldModel;
    updateSize();
}

void GWorldView::resize(int width, int height) {
    if (width < 1 || height < 1)
        throw std::runtime_error("Invalid screen size. Has to be > 0.");
    this->width = width;
    this->height = height;
    updateSize();
}

void GWorldView::updateSize() {
    if (gWorld != nullptr)
        gWorld->getActiveCamera()->resize(width, height);
    updateViewPort(width, height);
}
