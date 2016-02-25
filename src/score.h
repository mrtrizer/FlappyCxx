#ifndef SCORE_H
#define SCORE_H

#include "core/gobj.h"
#include "shapes/gdecor.h"

class Score: public GObj
{
public:
    Score(const GPos &);
    void init() override;
    void recalc(DeltaT, const GContext &) override;
    void setScore(int score){this->score = score;}
private:
    int score = 0;
    std::vector<std::shared_ptr<GDecor>> numbers;
};

#endif // SCORE_H
