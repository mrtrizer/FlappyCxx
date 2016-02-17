#ifndef GVIEWSHAPE_H
#define GVIEWSHAPE_H

#include "gview.h"

namespace GL_GView {

class GViewShape: public GView {
public:
    GViewShape();

    void draw(const GLfloat * pMatrix, const GLfloat * mvMatrix) override;

    virtual const AttribArray & getAttribArray() const = 0;
    const Shader & getShader() const {return shader;}

private:
    Shader shader;
};

class GViewCircle: public GViewShape {
public:
    GViewCircle(int vertexCnt);
    const AttribArray & getAttribArray() const override {return circle; }

private:
    int vertexCnt;
    AttribArray circle;
};

}

#endif // GVIEWSHAPE_H
