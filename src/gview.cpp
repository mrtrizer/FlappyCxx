#include "gview.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"

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

GView::GView() {
    //Init GL
    glClearColor(0, 0, 0, 0);

    //Init shader
    shader = new Shader(gVertexShader, gFragmentShader);

    Vertex triangleData[] = {
        {-1.0f,-1.0f},
        { 0.0f, 1.0f},
        { 1.0f,-1.0f}
    };
    triangle.addVBO<Vertex>(triangleData, sizeof(triangleData), GL_FLOAT,
                            glGetAttribLocation(shader->getProgram(), "aPosition"));

    Color colorData[] = {
        {1.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f, 1.0f}
    };
    triangle.addVBO<Color>(colorData, sizeof(colorData), GL_FLOAT,
                           glGetAttribLocation(shader->getProgram(), "aColor"));

    checkOpenGLerror();
}

GView::~GView() {

}

void GView::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void GView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->render(triangle, GL_TRIANGLES);
}
