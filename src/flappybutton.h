#ifndef FLAPPYBUTTON_H
#define FLAPPYBUTTON_H

#include <functional>

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewshape.h"

class FlappyButton : public GObj, public GColliderCircle, public GViewCircle {
public:
    typedef std::function<void()> OnClick;

    explicit FlappyButton(const OnClick & onClick, GPos pos = {0,0,0}):
        GObj(pos),
        GColliderCircle(3),
        GViewCircle(25,3),
        onClick(onClick)
    {}

    void recalc(DeltaT, GContext context) {
        if (context.getMouseEvent() == GContext::CLICK)
            onClick();
    }

private:
    OnClick onClick;
};

#endif // FLAPPYBUTTON_H
