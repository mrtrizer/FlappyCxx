#ifndef GVIEW_H
#define GVIEW_H

#include <GL/glew.h>
#include <vector>

class Shader;

/// View in MVC terms.
class GView {
public:
    typedef GLuint VBO;

    GView();
    ~GView();
    void redraw();
    void initShader();
    void resize(int width, int height);

private:
    struct Vertex {
      GLfloat x;
      GLfloat y;
    };

    Shader * shader;
    GLint  Attrib_vertex;
    GLint  Unif_color;
    GLuint vbo;

    template<typename ItemType>
    VBO createVBO(const ItemType * data, int size) {
        VBO vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        return vbo;
    }
};

#endif // GVIEW_H
