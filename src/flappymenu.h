#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"

class FlappyCtrl;

class FlappyMenu :public GWorldModel
{
public:
    FlappyMenu(FlappyCtrl & flappyCtrl):flappyCtrl(flappyCtrl){}
    void init();
    void click(int x, int y);

private:
    FlappyCtrl & flappyCtrl;
};

#endif // FLAPPYMENU_H
