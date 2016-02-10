#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"

class GObjCircle : public GObj_CRTP<GObjCircle> {
public:
    typedef double R;

    explicit GObjCircle(Id, R = 0, Pos = {0,0,0});
    inline void setR(R r) {this->r = r;}
    inline R getR() const {return r;}

private:
    R r = 0;
};

#endif // GOBJCIRCLE_H
