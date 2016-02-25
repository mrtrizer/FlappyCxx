#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "world.h"
#include "menu.h"
#include "gl/glworldview.h"
#include "core/gcontext.h"

class Ctrl {
public:
    typedef std::shared_ptr<GWorldView> GWorldViewP;
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    void init();
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    void step();
    void putSymbol(Symbol symbol);
    void setView(const GWorldViewP &gWorldView);
    inline int getScore() const {return score;}

private:
    std::shared_ptr<GWorldModel> curWorld;
    GWorldViewP gWorldView;
    GContext gContext;
    State state = MENU;
    int score;

    void setWorld(std::shared_ptr<GWorldModel> gWorld);
    State automat(Symbol symbol);
};

#endif // FLAPPYCTRL_H
