#include "gltexture.h"


GLTexture::GLTexture()
{
    struct Image {
        unsigned int width;
        unsigned int height;
    };
    Image image = {128,128};

    unsigned int data [128 * 128];

    for (int i = 0; i < image.width * image.height;i++)
        data[i] = 0xFF0000FF + i;

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)data);
    CHECK_GL_ERROR;
    glBindTexture(GL_TEXTURE_2D,0);
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
