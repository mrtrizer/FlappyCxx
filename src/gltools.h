#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <cstdio>

#include <GL/glew.h>

#ifdef QT_CORE_LIB
#include <QDebug>
#define  LOGI(...) qDebug(__VA_ARGS__)
#define  LOGE(...) qDebug(__VA_ARGS__)
#else
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}
#endif

namespace GLTools {

void checkOpenGLerror(const char * = "", const char * = "", int = 0);

}

#define CHECK_GL_ERROR GLTools::checkOpenGLerror(__FILE__, __FUNCTION__, __LINE__)

#endif // GLTOOLS_H
