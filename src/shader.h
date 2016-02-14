#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

#include "gltools.h"
#include "attribarray.h"

class Shader
{
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;
    typedef unsigned int Method;

    Shader(VertexSource, FragmentSource);
    ~Shader();
    inline Program getProgram() const {return program;}
    inline void bind() {glUseProgram(getProgram());}
    inline void unbind() {glUseProgram(0);}
    void render(const AttribArray &, Method);
private:
    Program program;

    GLuint loadShader(GLenum shaderType, const char* pSource);
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif // SHADER_H
