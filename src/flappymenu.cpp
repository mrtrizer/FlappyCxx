#include "flappymenu.h"
#include "flappyctrl.h"
#include "button.h"

FlappyMenu::FlappyMenu(FlappyCtrl &flappyCtrl):
    flappyCtrl(flappyCtrl)
{}

void FlappyMenu::init() {
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,100,1,500,POS(0,0,0)));
    getRoot()->ADD_CHILD(Button,[this](){
        flappyCtrl.putSymbol(FlappyCtrl::START);
    }, 10, 10, POS(0,0,0));
}
