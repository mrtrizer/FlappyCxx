#ifndef GVIEW_H
#define GVIEW_H

#include <GL/glew.h>
#include <vector>

#include "shader.h"
#include "gltools.h"
#include "attribarray.h"

class Shader;
class GWorld;

/// View in MVC terms.
class GView {
public:
    typedef int Width;
    typedef int Height;
    GView(GWorld &);
    ~GView();
    void redraw();
    void resize(Width, Height);

private:
    Width width;
    Height height;
    Shader shader;
    AttribArray triangle;
    GWorld &gWorld;
};

#endif // GVIEW_H
