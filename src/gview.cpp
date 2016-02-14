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

GView::GView(const GWorld &gWorld): gWorld(gWorld) {
    //Init GL
    glClearColor(0, 0, 0, 0);

    //Init shader
    shader = new Shader(gVertexShader, gFragmentShader);

    Vertex triangleData[] = {
        {-1.0f,-1.0f},
        { 0.0f, 1.0f},
        { 1.0f,-1.0f}
    };
    triangle.addVBO<Vertex>(triangleData, sizeof(triangleData), GL_FLOAT, shader->findAttr("aPosition"));

    Color colorData[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f}
    };
    triangle.addVBO<Color>(colorData, sizeof(colorData), GL_FLOAT, shader->findAttr("aColor"));

    checkOpenGLerror();
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

    shader->render(triangle, GL_TRIANGLES);
}
