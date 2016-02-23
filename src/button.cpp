#include "button.h"
#include "core/gobjpointer.h"
#include "core/gcontext.h"

Button::Button(const Button::OnClick &onClick, GPos pos):
    GObj(pos),
    GColliderCircle(3),
    GViewCircle(25,3),
    onClick(onClick)
{}

void Button::recalc(GObj::DeltaT, const GContext & context) {
    auto pointers = findIntersectObjs([](const GObj::GObjP & i){return typeid(*i) == typeid(GObjPointer);});
    if (pointers.size() == 1) {
        setColorRGBA({1.0,0,0,1.0});
        if (context.getMouseEvent() == GContext::CLICK)
            onClick();
    } else
        setColorRGBA({1.0,1.0,1.0,1.0});
}
