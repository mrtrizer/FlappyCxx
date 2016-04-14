#include "ctrl.h"
#include "core/gviewfactory.h"

/// World initialization
/// @see setWorld()
void Ctrl::init() {
    setWorld(std::make_shared<Menu>(*this));
}

/// Pass new symbol to the state machine.
/// @see FlappyMenu
/// @see FlappyWorld
void Ctrl::putSymbol(Ctrl::Symbol symbol) {
    symbols.push(symbol);
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
        break;
    case GAME: switch (symbol) {
        case STOP:
            score = std::dynamic_pointer_cast<World>(getCurWorld())->getScore();
            if (score > bestScore)
                bestScore = score;
            setWorld(std::make_shared<Menu>(*this));
            return MENU;
        default:;
        }
        break;
    default:
        LOGI("Invalid state. %d", state);
#ifdef QT_DEBUG
        throw std::runtime_error("");
#endif
        return state;
    }
    LOGI("Invalid symbol. %d", symbol);
#ifdef QT_DEBUG
    throw std::runtime_error("");
#endif
    return state;
}
