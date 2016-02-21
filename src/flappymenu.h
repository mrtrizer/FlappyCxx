#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"
#include "core/gobjcamera.h"
#include "shapes/gobjcircle.h"

class FlappyCtrl;

class FlappyMenu : public GWorldModel{
public:
    FlappyMenu(FlappyCtrl & flappyCtrl):
        flappyCtrl(flappyCtrl) {}

    virtual void init_() override {
        setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,100,1.0,POS(0,0,0)));
        getRoot()->ADD_CHILD(GObjCircle,5,POS(0,0,0));
    }
    void click(int x, int y);

private:
    FlappyCtrl & flappyCtrl;
};

#endif // FLAPPYMENU_H
