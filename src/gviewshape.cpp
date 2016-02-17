#include "gviewshape.h"

namespace GL_GView {

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

GViewShape::GViewShape() :
    shader(gVertexShader, gFragmentShader) {

}

void GViewShape::draw(const GLfloat * pMatrix, const GLfloat * mvMatrix) {
    shader.render(getAttribArray(), [this, mvMatrix, pMatrix](){
        glUniformMatrix4fv(shader.findUniform("uMVMatrix"),1,true,mvMatrix);
        glUniformMatrix4fv(shader.findUniform("uPMatrix"),1,true,pMatrix);
    });
}

GViewCircle::GViewCircle(int vertexCnt):
    vertexCnt(vertexCnt),
    circle(GL_TRIANGLE_FAN){
    std::vector<GLTools::Vertex> vertexList = GLTools::circleTriangleFan(1,vertexCnt);
    circle.addVBO<GLTools::Vertex>(vertexList.data(), vertexList.size() * sizeof(GLTools::Vertex), GL_FLOAT, getShader().findAttr("aPosition"));

    std::vector<GLTools::Color> colorList(vertexList.size());
    for (GLTools::Color & color: colorList)
        color = {1.0f, 1.0f, 1.0f, 1.0f};
    circle.addVBO<GLTools::Color>(colorList.data(), colorList.size() * sizeof(GLTools::Color), GL_FLOAT, getShader().findAttr("aColor"));
}

}
