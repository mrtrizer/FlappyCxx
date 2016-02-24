#ifndef GVIEWSPRITE_H
#define GVIEWSPRITE_H

#include "core/gview.h"
#include "glshaderprogram.h"
#include "glattribarray.h"
#include "gltexture.h"

class GLViewSprite : public GView
{
public:
    GLViewSprite(const std::shared_ptr<GLTexture> &glTexture, float width, float height);
    void draw(const PMatrix, const MVMatrix) override;

private:
    GLShaderProgram shader;
    GLAttribArray rect;
    std::shared_ptr<GLTexture> texture;
};

#endif // GVIEWSPRITE_H
