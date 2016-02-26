#ifndef GANIMATION_H
#define GANIMATION_H

#include "gdecor.h"

class GAnimation: public GDecor
{
public:
    GAnimation(std::string path, float width, float height, GPos pos, int frameCnt, float period);
    void recalc(DeltaT, const GContext &) override;
private:
    float counter = 0.0;
    float period = 0.0;
    int curFrame = 0;
};

#endif // GANIMATION_H
