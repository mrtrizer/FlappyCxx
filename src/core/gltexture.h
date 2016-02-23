#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "gltools.h"
#include "glshaderprogram.h"

class GLTexture
{
public:
    GLTexture();
    ~GLTexture() {} //TODO: glDeleteTexture
    void bind(GLShaderProgram::UniformLocation uniformLoc, int n);

private:
    GLuint texture;
};

#endif // GLTEXTURE_H
