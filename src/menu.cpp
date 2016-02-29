#include "menu.h"
#include "ctrl.h"
#include "button.h"
#include "score.h"
#include "core/gpresenter.h"
#include "core/ganimation.h"

Menu::Menu(Ctrl &flappyCtrl):
    flappyCtrl(flappyCtrl)
{}

void Menu::init() {
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,100,1,500,POS(0,0,0)));
    getRoot()->ADD_CHILD(GPresenterSprite,"logo",40,10,POS(-20,30,1));
    getRoot()->ADD_CHILD(GPresenterSprite,"background",200,200,POS(-100,-100,0));
    getRoot()->ADD_CHILD(GAnimation,"bird", 8, 10, POS(-4, 18 -4, 20),2,0.5);
    scorePanel = getRoot()->ADD_CHILD(Score,POS(-19, 18, 5));
    bestScorePanel = getRoot()->ADD_CHILD(Score,POS(6, 18, 5));
    getRoot()->ADD_CHILD(Button,[this](){
        flappyCtrl.putSymbol(Ctrl::START);
    }, 10, 10, POS(-5,-10,1));
}

void Menu::recalc(GObj::DeltaT, const GContext &){
    scorePanel->setScore(flappyCtrl.getScore());
    bestScorePanel->setScore(flappyCtrl.getBestScore());
}
