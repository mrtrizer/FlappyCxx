#include "gview.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "gworld.h"

using namespace std;

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

GView::GView(GWorld &gWorld):
    shader(gVertexShader, gFragmentShader),
    gWorld(gWorld) {

    LOGI("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0, 0, 0, 0);

    std::vector<GLTools::Vertex> vertexList = GLTools::circleTriangleFan(1,30);
    triangle.addVBO<GLTools::Vertex>(vertexList.data(), vertexList.size() * sizeof(GLTools::Vertex), GL_FLOAT, shader.findAttr("aPosition"));

    std::vector<GLTools::Color> colorList(vertexList.size());
    for (GLTools::Color & color: colorList)
        color = {1.0f, 1.0f, 1.0f, 1.0f};
    triangle.addVBO<GLTools::Color>(colorList.data(), colorList.size() * sizeof(GLTools::Color), GL_FLOAT, shader.findAttr("aColor"));

    CHECK_GL_ERROR;
}

GView::~GView() {

}

void GView::resize(Width width, Height height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void GView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float left = -10 * width / height;
    float right = 10 * width / height;
    float bottom = -10;
    float top = 10;
    float near = 0;
    float far = 100;

    GLfloat pMatrix[] = {
        2 / (right - left), 0, 0, (right + left) / (right - left),
        0, 2 / (top - bottom), 0, (top + bottom) / (top - bottom),
        0, 0, -2 / (far - near), (far + near) / (far - near),
        0, 0, 0, 1
    };
    GObjContainer::GObjPList root = gWorld.getObjTree().getChildsR();
    for (GObj * gObj: root) {
        GLfloat mvMatrix[] = {
            1, 0, 0, gObj->getPos().x,
            0, 1, 0, gObj->getPos().y,
            0, 0, 1, gObj->getPos().z,
            0, 0, 0, 1
        };

        shader.render(triangle, GL_TRIANGLE_FAN, [this, mvMatrix, pMatrix](){
            glUniformMatrix4fv(shader.findUniform("uMVMatrix"),1,true,mvMatrix);
            glUniformMatrix4fv(shader.findUniform("uPMatrix"),1,true,pMatrix);
        });
    }
}
