#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "world.h"
#include "menu.h"
#include "gl/glworldview.h"
#include "core/gcontext.h"

class Ctrl {
public:
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    Ctrl(const std::shared_ptr<GLWorldView> &gWorldView);
    void init();
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    void resize(int width, int height);
    void step();
    void glRedraw();
    void putSymbol(Symbol symbol);

private:
    std::shared_ptr<GWorldModel> curWorld;
    std::shared_ptr<GLWorldView> gWorldView;
    GContext gContext;
    State state = MENU;

    void setWorld(std::shared_ptr<GWorldModel> gWorld);
    State automat(Symbol symbol);
};

#endif // FLAPPYCTRL_H
