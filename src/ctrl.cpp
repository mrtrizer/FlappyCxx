#include "ctrl.h"
#include "core/gviewfactory.h"

/// Switch current world. It's used to switch between FlappyMenu and FlappyWorld
void Ctrl::setWorld(std::shared_ptr<GWorldModel> gWorld) {
    curWorld = gWorld;
    curWorld->initWorld();
    if (gWorldView != nullptr)
        setView(gWorldView);
}

/// World initialization
/// @see setWorld()
void Ctrl::init() {
    setWorld(std::make_shared<Menu>(*this));
}

/// Mouse click event
void Ctrl::mouseClick(int x, int y) {
    mouseMove(x,y);
    gContext.setMouseEvent(GContext::CLICK);
    curWorld->run(gContext);
}

/// Mouse move event
void Ctrl::mouseMove(int x, int y) {
    gContext.setX(x);
    gContext.setY(y);
}

/// Call a game loop step
void Ctrl::step() {
    curWorld->run(gContext);
    gContext.setMouseEvent(GContext::EMPTY);
}

/// Pass new symbol to the state machine.
/// @see FlappyMenu
/// @see FlappyWorld
void Ctrl::putSymbol(Ctrl::Symbol symbol) {
    state = automat(symbol);
}

void Ctrl::setView(const GWorldViewP &gWorldView){
    this->gWorldView = gWorldView;
    this->gWorldView->setGWorldModel(curWorld);
    this->gWorldView->init();
}

/// Handle new symbol and return new state
Ctrl::State Ctrl::automat(Ctrl::Symbol symbol) {
    switch (state) {
    case MENU: switch (symbol) {
        case START:
            setWorld(std::make_shared<World>(*this));
            return GAME;
        default:;
        }
    case GAME: switch (symbol) {
        case STOP:
            setWorld(std::make_shared<Menu>(*this));
            return MENU;
        default:;
        }
    default: throw std::runtime_error("Invalid state.");
    }
    throw std::runtime_error("Invalid symbol.");
}
