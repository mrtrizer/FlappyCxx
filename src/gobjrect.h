#ifndef GOBJRECT_H
#define GOBJRECT_H

#include "gobj.h"

class GObjRect: public GObj_CRTP<GObjRect> {
public:
    explicit GObjRect();
    virtual ~GObjRect(){}
};

#endif // GOBJRECT_H
