#ifndef FLAPPYMENU_H
#define FLAPPYMENU_H

#include "core/gworldmodel.h"

class Ctrl;
class Score;

/// Main menu world (scene)
class Menu :public GWorldModel
{
public:
    Menu(Ctrl & flappyCtrl);
    void init() override;
    void recalc(GObj::DeltaT, const GContext &) override;

private:
    Ctrl & flappyCtrl;
    std::shared_ptr<Score> scorePanel;
};

#endif // FLAPPYMENU_H
