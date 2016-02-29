#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "core/gobj.h"
#include "core/gcollider.h"
#include "core/gpresenter.h"

class Button : public GColliderRect {
public:
    typedef std::function<void()> OnClick;

    explicit Button(const OnClick & onClick, int width, int height, const GPos &pos);
    void recalc(DeltaT, const GContext &) override;
    void init();

private:
    OnClick onClick;
};

#endif // BUTTON_H
