#ifndef GL_SHADER_PROGRAM_H
#define GL_SHADER_PROGRAM_H


#ifdef QT_CORE_LIB
#include <GL/glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <iostream>
#include <functional>

#include "gltools.h"
#include "glattribarray.h"

class GLShaderProgram {
public:
    typedef const char * VertexSource;
    typedef const char * FragmentSource;
    typedef GLuint Program;
    typedef GLint AttribLocation;
    typedef const char * Name;
    typedef const std::function<void()>& UniformFunc;

    GLShaderProgram(VertexSource, FragmentSource);
    ~GLShaderProgram();
    void render(const GLAttribArray &, UniformFunc) const;
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

#endif // GL_SHADER_PROGRAM_H
