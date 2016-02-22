#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"

class FlappyCtrl;

/// Main menu world (scene)
class FlappyMenu :public GWorldModel
{
public:
    FlappyMenu(FlappyCtrl & flappyCtrl);
    void init();

private:
    FlappyCtrl & flappyCtrl;
};

#endif // FLAPPYMENU_H
