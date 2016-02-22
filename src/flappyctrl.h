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

    FlappyCtrl(){
        gWorldView = std::make_shared<GWorldView>();
        gContext = std::make_shared<GContext>(0,0,GContext::EMPTY);
    }

    void setWorld(std::shared_ptr<GWorldModel> gWorld) {
        curWorld = gWorld;
        curWorld->initWorld();
        gWorldView->setGWorldModel(curWorld);
        gWorldView->init();
    }

    void init() {
        setWorld(std::make_shared<FlappyMenu>(*this));
    }

    void click(int x, int y) {
        gContext = std::make_shared<GContext>(x,y,GContext::CLICK);
    }

    void resize(int width, int height) {
        gWorldView->resize(width, height);
    }

    void step() {
        curWorld->run(*gContext);
        gContext = std::make_shared<GContext>(0,0,GContext::EMPTY);
    }

    void glRedraw() {
        gWorldView->redraw();
    }

    void putSymbol(Symbol symbol) {
        state = automat(symbol);
    }
protected:
    State automat(Symbol symbol) {
        switch (state) {
        case MENU: switch (symbol) {
            case START:
                setWorld(std::make_shared<FlappyWorld>(*this));
                return GAME;
            }
        case GAME: switch (symbol) {
            case STOP:
                setWorld(std::make_shared<FlappyMenu>(*this));
                return MENU;
            }
        }
    }

private:
    std::shared_ptr<GWorldModel> curWorld;
    std::shared_ptr<GWorldView> gWorldView;
    std::shared_ptr<GContext> gContext;
    State state;
};

#endif // FLAPPYCTRL_H
