#ifndef SHADER_H
#define SHADER_H


#ifdef QT_CORE_LIB
#include <GL/glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <iostream>
#include <functional>

#include "gltools.h"
#include "attribarray.h"

//TODO: Rename to GLShaderProgram
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
