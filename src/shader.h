#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <functional>

#include "gltools.h"
#include "attribarray.h"

//TODO: Rename to ShaderProgram
class Shader {
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;
    typedef GLint AttribLocation;
    typedef const char * Name;
    typedef const std::function<void()>& UniformFunc;

    Shader(VertexSource, FragmentSource);
    ~Shader();
    void render(const AttribArray &, UniformFunc) const;
    AttribLocation findAttr(Name) const;
    AttribLocation findUniform(Name) const;
    inline Program getProgram() const {return program;}

    class shader_init_failed {};

protected:
    void bind() const;
    void unbind() const;

private:
    typedef GLenum ShaderType;
    typedef const char * ShaderSource;

    GLuint fragmentShader;
    GLuint vertexShader;
    Program program;

    GLuint loadShader(ShaderType, ShaderSource);
};

#endif // SHADER_H
