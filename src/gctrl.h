#ifndef GCTRL_H
#define GCTRL_H

#include <functional>

class GView;
class GWorldFlappy;

/// @brief Game Controller
/// @details Singlenton. Controller in MVC terms.
/// Instantiates GWorld and GView.
/// Handles input.
class GCtrl {
public:
    void start(std::function<void()>);
    void stop();
    void redraw();
    static GCtrl * getInst();
private:
    GCtrl();
    GCtrl(const GCtrl &){}
    ~GCtrl(){}
    static GCtrl * instance;
    GView * gView = nullptr;
    GWorldFlappy * gWorld = nullptr;
    std::function<void()> finishCb;
};

#endif // GCTRL_H
