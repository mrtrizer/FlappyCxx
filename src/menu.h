#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"

class Ctrl;

/// Main menu world (scene)
class Menu :public GWorldModel
{
public:
    Menu(Ctrl & flappyCtrl);
    void init();

private:
    Ctrl & flappyCtrl;
};

#endif // FLAPPYMENU_H
