#ifndef GVIEWSHAPE_H
#define GVIEWSHAPE_H

#include <memory>

#include "gview.h"
#include "gcollider.h"

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
    virtual const AttribArray & getAttribArray() const = 0;
    const Shader & getShader() const {return shader;}
    void setColorRGBA(ColorRGBA colorRGBA){this->colorRGBA = colorRGBA;}

private:
    Shader shader;
    ColorRGBA colorRGBA;
};

/// Circle shape (GL_TRIANGLE_FAN, vertexCnt points around the center point)
class GViewCircle: public GViewShape {
public:
    GViewCircle(int vertexCnt, double r);
    const AttribArray & getAttribArray() const override {return circle; }

private:
    int vertexCnt;
    AttribArray circle;

    std::vector<GLTools::Vertex> circleTriangleFan(float r, int count);
};

/// Rect shape (GL_TRIANGLE_STRIP, two triangles with a common side)
class GViewRect: public GViewShape {
public:
    GViewRect(float width, float height);
    const AttribArray & getAttribArray() const override {return rect;}

private:
    AttribArray rect;
};

#endif // GVIEWSHAPE_H
