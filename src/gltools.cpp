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

std::vector<Vertex> circleTriangleFan(R r, int count) {
    if (count < 3)
        throw too_few_vertices();
    std::vector<Vertex> vertexList(count + 2);
    float step = M_PI * 2 / count;
    vertexList[0] = Vertex({0,0});
    for (int i = 0; i < count + 1; i++)
        vertexList[i + 1] = {std::cos(step * i) * r, std::sin(step * i) * r};
    return vertexList;
}

}
