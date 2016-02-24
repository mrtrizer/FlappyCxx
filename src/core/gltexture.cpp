#include <cstring>

#include "gltexture.h"

//http://stackoverflow.com/questions/108318/whats-the-simplest-way-to-test-whether-a-number-is-a-power-of-2-in-c
bool isPowOfTwo(int x) {
    return !(x == 0) && !(x & (x - 1));
}

GLTexture::GLTexture(const uchar *bits, int width, int height):
    uvs({{0,0},{0,1},{1,0},{1,1}})
{
    const char * pixBuf = 0;
    int newWidth = 2;

    if ((width == height) && isPowOfTwo(width) && isPowOfTwo(height)) {
        pixBuf = reinterpret_cast<const char *>(bits);
        newWidth = width;
    } else {
        int oldWidth = width;
        int oldHeight = height;

        //max and nearest power of two
        newWidth = 1;
        do {
            newWidth <<= 1;
            oldWidth >>= 1;
            oldHeight >>= 1;
        } while (oldWidth || oldHeight);

        uvs[2].u = (float)width / newWidth;
        uvs[3].u = (float)width / newWidth;
        uvs[1].v = (float)height / newWidth;
        uvs[3].v = (float)height / newWidth;

        //data buffer for square image
        char * newPixBuf = new char[newWidth * newWidth * 4]();
        //image will be located at the top left corner of newPixBuf
        for (int i = 0; i < height; i++)
            std::memcpy(&newPixBuf[i * newWidth * 4], &bits[i * width * 4], width * 4);
        pixBuf = newPixBuf;
    }

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newWidth, newWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)pixBuf);
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


