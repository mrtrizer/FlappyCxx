#include "menu.h"
#include "ctrl.h"
#include "button.h"
#include "shapes/gdecor.h"

Menu::Menu(Ctrl &flappyCtrl):
    flappyCtrl(flappyCtrl)
{}

void Menu::init() {
    setActiveCamera(getRoot()->ADD_CHILD(GObjCamera,100,1,500,POS(0,0,0)));
    getRoot()->ADD_CHILD(GDecor,"background",200,200,POS(-100,-100,0));
    getRoot()->ADD_CHILD(GDecor,"bird", 8, 8, POS(-4, 20 -4, 20));
    getRoot()->ADD_CHILD(Button,[this](){
        flappyCtrl.putSymbol(Ctrl::START);
    }, 20, 10, POS(-10,-5,0));
}
