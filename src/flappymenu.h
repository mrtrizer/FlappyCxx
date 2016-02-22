#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"

class FlappyCtrl;

class FlappyMenu :public GWorldModel
{
public:
    FlappyMenu(FlappyCtrl & flappyCtrl):flappyCtrl(flappyCtrl){}
    void init();

private:
    FlappyCtrl & flappyCtrl;
};

#endif // FLAPPYMENU_H
