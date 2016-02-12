#ifndef GVIEW_H
#define GVIEW_H

#include <GL/glew.h>

class Shader;

/// View in MVC terms.
class GView {
public:
    GView();
    ~GView();
    void redraw();
    void initShader();
    void resize(int width, int height);

private:
    struct vertex {
      GLfloat x;
      GLfloat y;
    };

    Shader * shader;
    GLint  Attrib_vertex;
    GLint  Unif_color;
    GLuint VBO;
};

#endif // GVIEW_H
