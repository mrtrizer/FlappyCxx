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
    typedef std::shared_ptr<GWorldModel> GWorldModelP;
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    void init();
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    void step();
    void putSymbol(Symbol symbol);
    void setView(const GWorldViewP &gWorldView);
    inline int getScore() const {return score;}
    inline int getBestScore() const {return bestScore;}

private:
    std::shared_ptr<GWorldModel> curWorld;
    GWorldViewP gWorldView;
    std::queue<GContext> events;
    std::queue<Symbol> symbols;
    State state = MENU;
    int score = 0;
    int bestScore = 0;

    void setWorld(const GWorldModelP & gWorld);
    State automat(Symbol symbol);
};

#endif // FLAPPYCTRL_H
