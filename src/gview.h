#ifndef GVIEW_H
#define GVIEW_H

#include "shader.h"

class GView {
public:
    virtual ~GView(){}
    virtual void draw(const GLfloat *, const GLfloat *) = 0;
};

class GViewFake: public GView {
    void draw(const GLfloat *, const GLfloat *){}
};

//Replaces child of GView with GViewFake to avoid deal with OpenGL in model tests.
#ifdef NO_VIEW
template <typename View>
class GViewCustom : public GViewFake {
public:
    GViewCustom(...){}
};
#else
template <typename View>
class GViewCustom : public View {
public:
    using View::View;
};
#endif

#endif // GVIEW_H
