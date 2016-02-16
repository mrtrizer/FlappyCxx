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
        CHECK_GL_ERROR;
        glAttachShader(program, fragmentShader);
        CHECK_GL_ERROR;
        glLinkProgram(program);
        CHECK_GL_ERROR;
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
    CHECK_GL_ERROR;
    glDetachShader(program, fragmentShader);
    CHECK_GL_ERROR;
    glDeleteProgram(program);
    CHECK_GL_ERROR;
}

Shader::AttribLocation Shader::findAttr(Name name) const {
    return glGetAttribLocation(getProgram(), name);
}

Shader::AttribLocation Shader::findUniform(Name name) const {
    return glGetUniformLocation(getProgram(), name);
}

void Shader::bind() const {
    glUseProgram(getProgram());
    CHECK_GL_ERROR;
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::render(const AttribArray & attribArray, UniformFunc uniformFunc = [](){}) const {
    bind();
    uniformFunc();
    attribArray.bind();
    glDrawArrays(attribArray.getMethod(), 0, attribArray.getSize());
    attribArray.unbind();
    unbind();
}

GLuint Shader::loadShader(ShaderType shaderType, ShaderSource source) {
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)
        throw shader_init_failed();
    glShaderSource(shader, 1, &source, NULL);
    CHECK_GL_ERROR;
    glCompileShader(shader);
    CHECK_GL_ERROR;
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        PRINT_INFO(Shader, shader);
        glDeleteShader(shader);
        throw shader_init_failed();
    }
    return shader;
}
