#ifndef GVIEW_H
#define GVIEW_H

#include "shader.h"
#include "tools.h"

/// Interface for all object views.
/// Contains abstract draw() method for implementation in
/// derived classes.
class GView : public Tools::enable_shared_from_this_virtual<GView> {
public:
    typedef GLfloat * PMatrix;
    typedef GLfloat * MVMatrix;
    virtual ~GView(){}
    virtual void draw(const PMatrix, const MVMatrix) = 0;
};

#endif // GVIEW_H
