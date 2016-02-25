#ifndef GVIEWSPRITE_H
#define GVIEWSPRITE_H

#include "glview.h"
#include "glshaderprogram.h"
#include "glattribarray.h"
#include "gltexture.h"

class GLViewSprite : public GLView<GLViewSprite>
{
public:
    GLViewSprite(const std::shared_ptr<GLTexture> &glTexture, float width, float height);
    void draw(const PMatrix, const MVMatrix) override;

private:
    GLAttribArray rect;
    std::shared_ptr<GLTexture> texture;
};

#endif // GVIEWSPRITE_H
