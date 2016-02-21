#include "flappymenu.h"
#include "flappyctrl.h"

void FlappyMenu::click(int x, int y) {
    flappyCtrl.putSymbol(FlappyCtrl::START);
}

void FlappyMenu::init() {
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,10,1,POS(0,0,0)));
}
