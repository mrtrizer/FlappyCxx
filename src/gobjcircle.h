#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"

class GObjCircle : public GObj_CRTP<GObjCircle> {
public:
    explicit GObjCircle(Id);
    virtual ~GObjCircle(){}
    double getR(){return r;}

private:
    double r = 0;
};

#endif // GOBJCIRCLE_H
