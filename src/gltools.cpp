#include <iostream>
#include <exception>

#include "gltools.h"

namespace GLTools {

void checkOpenGLerror(const char * file, const char * func, int line) {
    GLenum errCode = glGetError();
    if(errCode != GL_NO_ERROR)
        LOGE("[ERROR] %s %s %d %s\n",file,func,line,gluErrorString(errCode));
#ifdef QT_DEBUG
    if(errCode != GL_NO_ERROR)
        throw std::runtime_error(reinterpret_cast<const char *>(gluErrorString(errCode)));
#endif
}

}
