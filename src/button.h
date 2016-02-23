#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gviewsprite.h"

/// Round button used in FlappyMenu
class Button : public GObj, public GColliderCircle, public GViewSprite {
public:
    typedef std::function<void()> OnClick;

    explicit Button(const OnClick & onClick, GPos pos = {0,0,0});
    void recalc(DeltaT, const GContext &) override;

private:
    OnClick onClick;
};

#endif // BUTTON_H
