#include <cstring>

#include "gltexture.h"


GLTexture::GLTexture(const uchar *bits, int width, int height):
    uvs({{0,0},{0,1},{1,0},{1,1}})
{
    int oldWidth = width;
    int oldHeight = height;
    //max and nearest power of two
    int newWidth = 1;
    do {
        newWidth <<= 1;
        oldWidth >>= 1;
        oldHeight >>= 1;
    } while (oldWidth || oldHeight);

    //data buffer for square image
    char * newPixBuf = new char[newWidth * newWidth * 4]();

    //image will be located at the top left corner of newPixBuf
    for (int i = 0; i < height; i++)
        std::memcpy(&newPixBuf[i * newWidth * 4], &bits[i * width * 4], width * 4);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    CHECK_GL_ERROR;
    glGenTextures(1, &texture);
    CHECK_GL_ERROR;
    glBindTexture(GL_TEXTURE_2D, texture);
    CHECK_GL_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    CHECK_GL_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    CHECK_GL_ERROR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newWidth, newWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)newPixBuf);
    CHECK_GL_ERROR;
    glBindTexture(GL_TEXTURE_2D,0);
    CHECK_GL_ERROR;
}

GLTexture::~GLTexture() {
    glDeleteTextures(1,&texture);
    CHECK_GL_ERROR;
}

void GLTexture::bind(GLShaderProgram::UniformLocation uniformLoc, int n) {
    glActiveTexture(GL_TEXTURE0 + n);
    CHECK_GL_ERROR;
    glBindTexture(GL_TEXTURE_2D, texture);
    CHECK_GL_ERROR;
    glUniform1i(uniformLoc, 0);
    CHECK_GL_ERROR;
}


