#include "gworldview.h"
#include "gobjcamera.h"
#include "gworldmodel.h"

void GWorldView::setGWorldModel(GWorldModelP gWorldModel) {
    this->gWorld = gWorldModel;
    resize(lastWidth,lastHeight);
}

void GWorldView::resize(int width, int height) {
    this->lastWidth = width;
    this->lastHeight = height;
    if (gWorld != nullptr) {
        gWorld->getActiveCamera()->resize(width, height);
    }
    updateViewPort();
}
