#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <cstdio>
#include <memory>
#include <cmath>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#ifdef QT_CORE_LIB
#include <QDebug>
#define  LOGI(...) qDebug(__VA_ARGS__)
#define  LOGE(...) qDebug(__VA_ARGS__)
#else
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}
#endif

namespace GLTools {

typedef float R;

struct Vertex {
  GLfloat x;
  GLfloat y;
};

void checkOpenGLerror(const char * = "", const char * = "", int = 0);

}

#define CHECK_GL_ERROR GLTools::checkOpenGLerror(__FILE__, __FUNCTION__, __LINE__)

#endif // GLTOOLS_H
