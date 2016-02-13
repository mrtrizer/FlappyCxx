#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;

    Shader(VertexSource, FragmentSource);
    ~Shader();
    inline Program getProgram() const {return program;}
    inline void use() {glUseProgram(getProgram());}
    inline void refuse() {glUseProgram(0);}
private:
    Program program;

    GLuint loadShader(GLenum shaderType, const char* pSource);
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif // SHADER_H
