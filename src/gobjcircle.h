#ifndef GOBJCIRCLE_H
#define GOBJCIRCLE_H

#include "gobj.h"

class GObjCircle : public GObj
{
public:
    explicit GObjCircle(const GWorld &);
    virtual ~GObjCircle(){}
    double getR(){return r;}

private:
    double r = 0;
};

#endif // GOBJCIRCLE_H
