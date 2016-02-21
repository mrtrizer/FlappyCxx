#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "flappyworld.h"
#include "core/gworldview.h"

class FlappyCtrl {
public:
    enum State {MENU, GAME};
    enum Symbol {START, STOP};

    FlappyCtrl(){
        gWorldView = std::make_shared<GWorldView>();
    }

    void setWorld(std::shared_ptr<GWorldModel> gWorld) {
        curWorld = gWorld;
        curWorld->initWorld();
        gWorldView->setGWorldModel(curWorld);
        gWorldView->init();
    }

    void init() {
        setWorld(std::make_shared<FlappyWorld>());
    }

    void click(int x, int y) {
        if (typeid(*curWorld) == typeid(FlappyWorld))
            std::dynamic_pointer_cast<FlappyWorld>(curWorld)->flap();
    }

    void resize(int width, int height) {
        gWorldView->resize(width, height);
    }

    void step() {
        curWorld->run();
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
                setWorld(std::make_shared<FlappyWorld>());
                return GAME;
            }
        case GAME: switch (symbol) {
            case STOP:
                setWorld(std::make_shared<FlappyWorld>());
                return MENU;
            }
        }
    }

private:
    std::shared_ptr<GWorldModel> curWorld;
    std::shared_ptr<GWorldView> gWorldView;
    State state;
};

#endif // FLAPPYCTRL_H
