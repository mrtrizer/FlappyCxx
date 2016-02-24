#include "flappyctrl.h"
#include "core/gviewfactory.h"

FlappyCtrl::FlappyCtrl(){
    gWorldView = std::make_shared<GWorldView>(std::make_shared<GLViewFactoryDesktop>());
}

/// Switch current world. It's used to switch between FlappyMenu and FlappyWorld
void FlappyCtrl::setWorld(std::shared_ptr<GWorldModel> gWorld) {
    curWorld = gWorld;
    curWorld->initWorld();
    gWorldView->setGWorldModel(curWorld);
    gWorldView->init();
}

/// World initialization
/// @see setWorld()
void FlappyCtrl::init() {
    setWorld(std::make_shared<FlappyMenu>(*this));
}

/// Mouse click event
void FlappyCtrl::mouseClick(int x, int y) {
    mouseMove(x,y);
    gContext.setMouseEvent(GContext::CLICK);
}

/// Mouse move event
void FlappyCtrl::mouseMove(int x, int y) {
    gContext.setX(x);
    gContext.setY(y);
}

/// Resize View
/// @see GObjCamera
/// @see GWorldView
void FlappyCtrl::resize(int width, int height) {
    gWorldView->resize(width, height);
}

/// Call a game loop step
void FlappyCtrl::step() {
    curWorld->run(gContext);
    gContext.setMouseEvent(GContext::EMPTY);
}

/// Redraw View
void FlappyCtrl::glRedraw() {
    gWorldView->redraw();
}

/// Pass new symbol to the state machine.
/// @see FlappyMenu
/// @see FlappyWorld
void FlappyCtrl::putSymbol(FlappyCtrl::Symbol symbol) {
    state = automat(symbol);
}

/// Handle new symbol and return new state
FlappyCtrl::State FlappyCtrl::automat(FlappyCtrl::Symbol symbol) {
    switch (state) {
    case MENU: switch (symbol) {
        case START:
            setWorld(std::make_shared<FlappyWorld>(*this));
            return GAME;
        default:;
        }
    case GAME: switch (symbol) {
        case STOP:
            setWorld(std::make_shared<FlappyMenu>(*this));
            return MENU;
        default:;
        }
    default: throw std::runtime_error("Invalid state.");
    }
    throw std::runtime_error("Invalid symbol.");
}
