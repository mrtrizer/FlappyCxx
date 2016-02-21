#ifndef GWORLDCTRL_H
#define GWORLDCTRL_H

template <typename Symbol, typename State>
class GWorldCtrl {
public:
    GWorldCtrl(State state):
        state(state) {}

    void putSymbol(Symbol symbol) {
        state = automat(state, symbol);
    }

    inline State getState() const {return state;}

protected:
    virtual State automat(State state, Symbol symbol) = 0;

private:
    State state;
};

#endif // GWORLDCTRL_H
