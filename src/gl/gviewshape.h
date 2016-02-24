#ifndef GVIEWSHAPE_H
#define GVIEWSHAPE_H

#include <memory>

#include "core/gview.h"
#include "glshaderprogram.h"
#include "glattribarray.h"
#include "gltools.h"

/// Contains shader for all shapes and draw implementation.
/// All derived classes have to impmelent getAttribArray().
class GViewShape: public GView {
public:
    struct ColorRGBA {
      GLfloat r;
      GLfloat g;
      GLfloat b;
      GLfloat a;
    };

    GViewShape();
    void draw(const PMatrix, const MVMatrix) override;
    virtual const GLAttribArray & getAttribArray() const = 0;
    const GLShaderProgram & getShader() const {return shader;}
    void setColorRGBA(ColorRGBA colorRGBA){this->colorRGBA = colorRGBA;}

private:
    GLShaderProgram shader;
    ColorRGBA colorRGBA;
};

/// Circle shape (GL_TRIANGLE_FAN, vertexCnt points around the center point)
class GViewCircle: public GViewShape {
public:
    GViewCircle(int vertexCnt, double r);
    const GLAttribArray & getAttribArray() const override {return circle; }

private:
    int vertexCnt;
    GLAttribArray circle;

    std::vector<GLTools::Vertex> circleTriangleFan(float r, int count);
};

/// Rect shape (GL_TRIANGLE_STRIP, two triangles with a common side)
class GViewRect: public GViewShape {
public:
    GViewRect(float width, float height);
    const GLAttribArray & getAttribArray() const override {return rect;}

private:
    GLAttribArray rect;
};

#endif // GVIEWSHAPE_H
