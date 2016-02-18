#ifndef GVIEW_H
#define GVIEW_H

#include "shader.h"
#include "tools.h"

class GView : public Tools::enable_shared_from_this_virtual<GView> {
public:
    virtual ~GView(){}
    virtual void draw(const GLfloat *, const GLfloat *) = 0;
};

#endif // GVIEW_H
