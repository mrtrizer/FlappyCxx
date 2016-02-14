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
    "varying vec4 vColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPosition,0,1);\n"
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

    Vertex triangleData[] = {
        {-1.0f,-1.0f},
        { 0.0f, 1.0f},
        { 1.0f,-1.0f}
    };
    triangle.addVBO<Vertex>(triangleData, sizeof(triangleData), GL_FLOAT, shader.findAttr("aPosition"));

    Color colorData[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f}
    };
    triangle.addVBO<Color>(colorData, sizeof(colorData), GL_FLOAT, shader.findAttr("aColor"));

    CHECK_GL_ERROR;
}

GView::~GView() {

}

void GView::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void GView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GObjContainer::GObjPList root = gWorld.getObjTree().getChildsR();
    for (GObj * gObj: root) {

    }

    shader.render(triangle, GL_TRIANGLES);
}
