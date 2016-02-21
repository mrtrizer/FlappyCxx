#ifndef FLAPPYCTRL_H
#define FLAPPYCTRL_H

#include <memory>

#include "flappyworld.h"
#include "flappymenu.h"
#include "core/gworldview.h"
#include "core/gworldctrl.h"

enum FlappyState {MENU, GAME};
enum FlappySymbol {START, GAME_OVER};

class FlappyCtrl : public GWorldCtrl<FlappySymbol, FlappyState> {
public:

    FlappyCtrl():GWorldCtrl(MENU){
        flappyMenu = std::make_shared<FlappyMenu>(*this);
        flappyWorld = std::make_shared<FlappyWorld>(*this);
        gWorldView = std::make_shared<GWorldView>();
    }

    void switchWorld(std::shared_ptr<GWorldModel> gWorldModel) {
        gWorldView->getGWorldModel()->deinit();
        gWorldView->setGWorldModel(gWorldModel);
    }

    void init() {
        gWorldView->init();
        gWorldView->setGWorldModel(flappyMenu);
    }

    void click(int x, int y) {
        switch (getState()) {
            case MENU: flappyMenu->click(x,y); break;
            case GAME: flappyWorld->flap(); break;
        }

    }

    void resize(int width, int height) {
        gWorldView->resize(width, height);
    }

    void step() {
        switch (getState()) {
            case MENU: flappyMenu->run(); break;
            case GAME: flappyWorld->run(); break;
        }

    }

    void glRedraw() {
        gWorldView->redraw();
    }

protected:
    FlappyState automat(FlappyState state, FlappySymbol symbol) {
        switch (state) {
            case MENU: switch (symbol) {
                case START: switchWorld(flappyWorld); return GAME;
            }
            case GAME: switch (symbol) {
                case GAME_OVER: switchWorld(flappyMenu); return MENU;
            }
        }
        return state;
    }

private:
    std::shared_ptr<FlappyWorld> flappyWorld;
    std::shared_ptr<FlappyMenu> flappyMenu;
    std::shared_ptr<GWorldView> gWorldView;
};

#endif // FLAPPYCTRL_H
