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
    events.push(GContext(x,y,GContext::CLICK));
}

/// Mouse move event
void Ctrl::mouseMove(int x, int y) {
    events.push(GContext(x,y,GContext::EMPTY));
}

/// Call a game loop step
void Ctrl::step() {
    //if events not empty, repeat a game loop iteration
    //for every event. else, run once with empty event.
    if (events.size() == 0) {
        curWorld->run(GContext(0,0,GContext::EMPTY));
        while (symbols.size() > 0) {
            state = automat(symbols.front());
            symbols.pop();
        }
    } else {
        while (events.size() > 0) {
            curWorld->run(events.front());
            events.pop();
            //check symbols after iteration
            while (symbols.size() > 0) {
                state = automat(symbols.front());
                symbols.pop();
            }
        }
    }

}

/// Pass new symbol to the state machine.
/// @see FlappyMenu
/// @see FlappyWorld
void Ctrl::putSymbol(Ctrl::Symbol symbol) {
    symbols.push(symbol);
}

void Ctrl::setView(const GWorldViewP &gWorldView){
    this->gWorldView = gWorldView;
    this->gWorldView->setGWorldModel(curWorld);
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
            score = std::dynamic_pointer_cast<World>(curWorld)->getScore();
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
