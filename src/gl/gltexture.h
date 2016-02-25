#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <vector>

#include "gltools.h"
#include "glshaderprogram.h"

class GLTexture {
public:
    struct UV {
        GLfloat u;
        GLfloat v;
    };

    GLTexture(const char * bits, int width, int height);
    ~GLTexture();
    void bind(GLShaderProgram::UniformLocation uniformLoc, int n);
    inline std::vector<UV> getUVs() const { return uvs; }
    inline float getRelWidth() const {return relWidth;}
    inline float getRelHeight() const {return relHeight;}

private:
    GLuint texture;
    std::vector<UV> uvs;
    float relWidth;
    float relHeight;
};

#endif // GLTEXTURE_H
