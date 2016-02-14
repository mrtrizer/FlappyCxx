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

Shader::Shader(VertexSource vertexSource, FragmentSource fragmentSource) {
    vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);

    program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        //checkGlError("glAttachShader");
        glAttachShader(program, fragmentShader);
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
}

Shader::~Shader() {
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteProgram(program);
}

Shader::AttribLocation Shader::findAttr(AttribName name) const {
    return glGetAttribLocation(getProgram(), name);
}

void Shader::bind() {
    glUseProgram(getProgram());
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::render(const AttribArray & attribArray, Method method) {
    bind();
    attribArray.bind();
    glDrawArrays(method, 0, attribArray.getSize());
    attribArray.unbind();
    unbind();
}

GLuint Shader::loadShader(ShaderType shaderType, ShaderSource source) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &source, NULL);
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
