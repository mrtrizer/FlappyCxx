#include <string>
#include <iostream>

#include "shader.h"

using namespace std;

#define PRINT_INFO(type, instance) { \
    GLint infoLen = 0; \
    glGet ## type ## iv(instance, GL_INFO_LOG_LENGTH, &infoLen); \
    if (infoLen) { \
        char buf[infoLen]; \
        glGet ## type ## InfoLog(instance, infoLen, NULL, buf); \
        std::cout << "Could not compile shader:" << std::endl << buf << std::endl; \
    } \
}

Shader::Shader(VertexSource pVertexSource, FragmentSource pFragmentSource) {
    program = createProgram(pVertexSource, pFragmentSource);
}

Shader::~Shader() {
    unbind();
    glDeleteProgram(program);
}

Shader::AttribLocation Shader::findAttr(AttribName name) const {
    return glGetAttribLocation(getProgram(), name);
}

void Shader::render(const AttribArray & attribArray, Method method) {
    bind();
    attribArray.bind();
    glDrawArrays(method, 0, attribArray.getSize());
    attribArray.unbind();
    unbind();
}

GLuint Shader::loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            PRINT_INFO(Shader, shader);
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint Shader::createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    Program program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        //checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        //checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            PRINT_INFO(Program, program);
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}
