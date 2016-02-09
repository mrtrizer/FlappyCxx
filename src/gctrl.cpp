#include "gctrl.h"
#include "gview.h"

GCtrl * GCtrl::instance = nullptr;

GCtrl::GCtrl() {

}

GCtrl * GCtrl::getInst() {
    if (instance == 0)
        instance = new GCtrl();
    return instance;
}

void GCtrl::start(std::function<void()> finishCb) {
    this->finishCb = finishCb;
}

void GCtrl::stop() {

}
