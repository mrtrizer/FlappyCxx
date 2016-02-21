#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "flappyworld.h"
#include "core/gworldview.h"

class FlappyCtrl {
public:
    FlappyCtrl(){
        flappyWorld = std::make_shared<FlappyWorld>();
        gWorldView = std::make_shared<GWorldView>();
    }

    void init() {
        gWorldView->init();
        gWorldView->setGWorldModel(flappyWorld);
    }

    void click(int x, int y) {
        flappyWorld->flap();
    }

    void resize(int width, int height) {
        gWorldView->resize(width, height);
    }

    void step() {
        flappyWorld->run();
    }

    void glRedraw() {
        gWorldView->redraw();
    }

private:
    std::shared_ptr<FlappyWorld> flappyWorld;
    std::shared_ptr<GWorldView> gWorldView;
};

#endif // FLAPPYCTRL_H
