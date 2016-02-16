#ifndef GVIEWSHAPE_H
#define GVIEWSHAPE_H

#include "shader.h"

class GView {
public:
    virtual ~GView(){}
    virtual void draw(const GLfloat * pMatrix, const GLfloat * mvMatrix) = 0;
};

class GViewShape: public GView {
public:
    GViewShape();
};

static const char gVertexShader[] =
    "attribute vec2 aPosition;\n"
    "attribute vec4 aColor;\n"
    "uniform mat4 uMVMatrix;\n"
    "uniform mat4 uPMatrix;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "   gl_Position = uPMatrix * uMVMatrix * vec4(aPosition,0,1);\n"
    "   vColor = aColor;"
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;\n"
    "varying vec4 vColor;\n"
    "void main() {\n"
    "   gl_FragColor = vColor;\n"
    "}\n";

class GViewCircle: public GViewShape {
public:
    GViewCircle(int vertexCnt):
        vertexCnt(vertexCnt),
        shader(gVertexShader, gFragmentShader){
        std::vector<GLTools::Vertex> vertexList = GLTools::circleTriangleFan(1,vertexCnt);
        triangle.addVBO<GLTools::Vertex>(vertexList.data(), vertexList.size() * sizeof(GLTools::Vertex), GL_FLOAT, shader.findAttr("aPosition"));

        std::vector<GLTools::Color> colorList(vertexList.size());
        for (GLTools::Color & color: colorList)
            color = {1.0f, 1.0f, 1.0f, 1.0f};
        triangle.addVBO<GLTools::Color>(colorList.data(), colorList.size() * sizeof(GLTools::Color), GL_FLOAT, shader.findAttr("aColor"));
    }
    void draw(const GLfloat * pMatrix, const GLfloat * mvMatrix) override {
        shader.render(triangle, GL_TRIANGLE_FAN, [this, mvMatrix, pMatrix](){
            glUniformMatrix4fv(shader.findUniform("uMVMatrix"),1,true,mvMatrix);
            glUniformMatrix4fv(shader.findUniform("uPMatrix"),1,true,pMatrix);
        });
    }
private:
    int vertexCnt;
    Shader shader;
    AttribArray triangle;
};

#endif // GVIEWSHAPE_H
