#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "flappyworld.h"
#include "flappymenu.h"
#include "core/gworldview.h"

class FlappyCtrl {
public:
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    FlappyCtrl();
    void init();
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    void resize(int width, int height);
    void step();
    void glRedraw();
    void putSymbol(Symbol symbol);

private:
    std::shared_ptr<GWorldModel> curWorld;
    std::shared_ptr<GWorldView> gWorldView;
    GContext gContext;
    State state;

    void setWorld(std::shared_ptr<GWorldModel> gWorld);
    State automat(Symbol symbol);
};

#endif // FLAPPYCTRL_H
