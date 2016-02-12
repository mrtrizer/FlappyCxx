#include "gview.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"

#ifdef QT_CORE_LIB
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)
#else
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}
#endif

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

static const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "uniform vec4 vColor;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

void checkOpenGLerror() {
  GLenum errCode;
  if((errCode=glGetError()) != GL_NO_ERROR)
    std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

void GView::initShader() {
  const char* attr_name = "vPosition";
  Attrib_vertex = glGetAttribLocation(shader->getProgram(), attr_name);
  if(Attrib_vertex == -1) {
    std::cout << "could not bind attrib " << attr_name << std::endl;
    return;
  }
  const char* unif_name = "vColor";
  Unif_color = glGetUniformLocation(shader->getProgram(), unif_name);
  if(Unif_color == -1) {
    std::cout << "could not bind uniform " << unif_name << std::endl;
    return;
  }

  checkOpenGLerror();
}

GView::GView() {
    //Init GL
    glClearColor(0, 0, 0, 0);

    //Init VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    vertex triangle[3] = {
        {-1.0f,-1.0f},
        { 0.0f, 1.0f},
        { 1.0f,-1.0f}
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    checkOpenGLerror();

    //Init shader
    shader = new Shader(gVertexShader, gFragmentShader);

    //Init vars
    initShader();
}

GView::~GView() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
}

void GView::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void GView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    shader->use();
    static float red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    glUniform4fv(Unif_color, 1, red);
    glEnableVertexAttribArray(Attrib_vertex);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glVertexAttribPointer(Attrib_vertex, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(Attrib_vertex);
    shader->refuse();
    checkOpenGLerror();
}
