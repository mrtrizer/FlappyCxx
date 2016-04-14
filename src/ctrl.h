#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include <core/gcontext.h>
#include <core/gworldctrl.h>

#include "menu.h"
#include "world.h"

class Ctrl: public GWorldCtrl {
public:
    typedef std::shared_ptr<GWorldView> GWorldViewP;
    typedef std::shared_ptr<GWorldModel> GWorldModelP;
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    void init() override;
    void mouseClick(int x, int y);
    void mouseMove(int x, int y);
    void step();
    void putSymbol(Symbol symbol);
    inline int getScore() const {return score;}
    inline int getBestScore() const {return bestScore;}

protected:
    void procState() override {
        while (symbols.size() > 0) {
            state = automat(symbols.front());
            symbols.pop();
        }
    }

private:
    std::queue<Symbol> symbols;
    State state = MENU;
    int score = 0;
    int bestScore = 0;

    State automat(Symbol symbol);
};

#endif // FLAPPYCTRL_H
