#include "button.h"
#include "core/gobjpointer.h"
#include "core/gcontext.h"

Button::Button(const Button::OnClick &onClick, int width, int height, const GPos & pos):
    GColliderRect(width,height,pos),
    onClick(onClick)
{}

void Button::init() {
    ADD_CHILD(GPresenterSprite,"start",getWidth(),getHeight());
}

void Button::recalc(GObj::DeltaT, const GContext & context) {
    auto pointers = findIntersectObjs([](const GObj::GObjP & i){return typeid(*i) == typeid(GObjPointer);});
    if (pointers.size() == 1)
        if (context.getMouseEvent() == GContext::CLICK) {
            onClick();
        }
}
