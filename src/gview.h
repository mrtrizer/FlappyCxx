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
    GView(GWorld &);
    ~GView();
    void redraw();
    void resize(int width, int height);

private:
    struct Vertex {
      GLfloat x;
      GLfloat y;
    };

    struct Color {
      GLfloat r;
      GLfloat g;
      GLfloat b;
      GLfloat a;
    };

    Shader shader;
    AttribArray triangle;
    GWorld &gWorld;
};

#endif // GVIEW_H
