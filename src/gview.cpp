#include "gview.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "gworld.h"
#include "gobjcamera.h"
#include "gobjcircle.h"

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
    glEnable(GL_MULTISAMPLE);

    std::vector<GLTools::Vertex> vertexList = GLTools::circleTriangleFan(1,30);
    triangle.addVBO<GLTools::Vertex>(vertexList.data(), vertexList.size() * sizeof(GLTools::Vertex), GL_FLOAT, shader.findAttr("aPosition"));

    std::vector<GLTools::Color> colorList(vertexList.size());
    for (GLTools::Color & color: colorList)
        color = {1.0f, 1.0f, 1.0f, 1.0f};
    triangle.addVBO<GLTools::Color>(colorList.data(), colorList.size() * sizeof(GLTools::Color), GL_FLOAT, shader.findAttr("aColor"));

    CHECK_GL_ERROR;
}

GView::~GView() {
    glDisable(GL_MULTISAMPLE);
}

void GView::resize(Width width, Height height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void GView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Find GObjCamera object
    std::shared_ptr<GObj> gObj = nullptr;
    try {
        gObj = gWorld.getRoot()->findChildR([](const GObj::GObjP & i) {
            return std::dynamic_pointer_cast<GObjCamera>(i) != nullptr;
        });
    } catch (GObjContainer::no_child_with_id_exception &) {
        throw std::runtime_error("Can't find camera object. Add GObjCamera object to your tree.");
    }

    std::shared_ptr<GObjCamera> gObjCamera = std::dynamic_pointer_cast<GObjCamera>(gObj);

    //Calc ortho matrix, using GObjCamera
    const float offset = gObjCamera->getHeight() / 2.0;
    GObj::Pos pos = gObjCamera->getPosAbsolute();
    const float left = -offset * width / height - pos.x;
    const float right = offset * width / height - pos.x;
    const float bottom = -offset - pos.y;
    const float top = offset - pos.y;
    static const float near = 0.0f;
    static const float far = 100.0f;

    GLfloat pMatrix[] = {
        2.0f / (right - left), 0, 0, (right + left) / (right - left),
        0, 2.0f / (top - bottom), 0, (top + bottom) / (top - bottom),
        0, 0, -2.0f / (far - near), (far + near) / (far - near),
        0, 0, 0, 1.0f
    };

    //For all children recursively
    GObjContainer::GObjPList root = gWorld.getRoot()->getChildsR();
    for (std::shared_ptr<GObj> gObj: root) {

        //If it's a visible object
        if (std::dynamic_pointer_cast<GObjCircle>(gObj) == nullptr)
            continue;

        GObj::Pos pos = gObj->getPosAbsolute();
        GLfloat mvMatrix[] = {
            1.0f, 0, 0, pos.x,
            0, 1.0f, 0, pos.y,
            0, 0, 1.0f, pos.z,
            0, 0, 0, 1.0f
        };

        shader.render(triangle, GL_TRIANGLE_FAN, [this, mvMatrix, pMatrix](){
            glUniformMatrix4fv(shader.findUniform("uMVMatrix"),1,true,mvMatrix);
            glUniformMatrix4fv(shader.findUniform("uPMatrix"),1,true,pMatrix);
        });
    }
}
