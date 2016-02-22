#include "flappymenu.h"
#include "flappyctrl.h"
#include "flappybutton.h"

void FlappyMenu::init() {
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,10,1,POS(0,0,0)));
    getRoot()->ADD_CHILD(FlappyButton,[this](){
        flappyCtrl.putSymbol(FlappyCtrl::START);
    }, POS(0,0,0));
}
