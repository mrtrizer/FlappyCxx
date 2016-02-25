#include "ctrl.h"
#include "core/gviewfactory.h"

Ctrl::Ctrl(const std::shared_ptr<GLWorldView> &gWorldView):
    gWorldView(gWorldView)
{}

/// Switch current world. It's used to switch between FlappyMenu and FlappyWorld
void Ctrl::setWorld(std::shared_ptr<GWorldModel> gWorld) {
    curWorld = gWorld;
    curWorld->initWorld();
    gWorldView->setGWorldModel(curWorld);
    gWorldView->init();
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
}

/// Mouse move event
void Ctrl::mouseMove(int x, int y) {
    gContext.setX(x);
    gContext.setY(y);
}

/// Resize View
/// @see GObjCamera
/// @see GWorldView
void Ctrl::resize(int width, int height) {
    gWorldView->resize(width, height);
}

/// Call a game loop step
void Ctrl::step() {
    curWorld->run(gContext);
    gContext.setMouseEvent(GContext::EMPTY);
}

/// Redraw View
void Ctrl::glRedraw() {
    gWorldView->redraw();
}

/// Pass new symbol to the state machine.
/// @see FlappyMenu
/// @see FlappyWorld
void Ctrl::putSymbol(Ctrl::Symbol symbol) {
    state = automat(symbol);
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