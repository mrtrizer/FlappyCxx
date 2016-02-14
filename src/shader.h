#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <functional>

#include "gltools.h"
#include "attribarray.h"

class Shader {
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;
    typedef unsigned int Method;
    typedef GLint AttribLocation;
    typedef const char * Name;
    typedef const std::function<void()>& UniformFunc;

    Shader(VertexSource, FragmentSource);
    ~Shader();
    void render(const AttribArray &, Method, UniformFunc);
    AttribLocation findAttr(Name) const;
    AttribLocation findUniform(Name) const;
    inline Program getProgram() const {return program;}

    class shader_init_failed {};

protected:
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
