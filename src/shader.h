#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

#include "gltools.h"
#include "attribarray.h"

class Uniform {
public:
    Uniform();
};

class Shader {
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;
    typedef unsigned int Method;
    typedef GLint AttribLocation;
    typedef const char * AttribName;

    Shader(VertexSource, FragmentSource);
    ~Shader();
    void render(const AttribArray &, Method);
    AttribLocation findAttr(AttribName) const;

    class shader_init_failed {};

protected:
    inline Program getProgram() const {return program;}
    void bind();
    void unbind();

private:
    typedef GLenum ShaderType;
    typedef const char * ShaderSource;

    GLuint fragmentShader;
    GLuint vertexShader;
    Program program;

    GLuint loadShader(ShaderType, ShaderSource);
};

#endif // SHADER_H
