#include "glviewsprite.h"

static const char spriteVShader[] =
    "attribute vec2 aPosition;\n"
    "attribute vec2 aTexCoord;\n"
    "uniform mat4 uMVMatrix;\n"
    "uniform mat4 uPMatrix;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "   vTexCoord = aTexCoord;"
    "   gl_Position = uPMatrix * uMVMatrix * vec4(aPosition,0,1);\n"
    "}\n";

static const char spriteFShader[] =
    "precision mediump float;\n"
    "uniform sampler2D uTex;\n"
    "uniform vec4 uColor;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(uTex,vTexCoord).bgra;\n"
    "}\n";

GLViewSprite::GLViewSprite(const std::shared_ptr<GLTexture> &glTexture, float width, float height) :
    GLView<GLViewSprite>(spriteVShader, spriteFShader),
    rect(GL_TRIANGLE_STRIP),
    texture(glTexture){

    std::vector<GLTools::Vertex> vertexList({
                                                {0,0},
                                                {0,height},
                                                {width,0},
                                                {width,height}
                                            });

    rect.addVBO<GLTools::Vertex>(vertexList.data(),
                                 vertexList.size() * sizeof(GLTools::Vertex),
                                 GL_FLOAT,
                                 getShader()->findAttr("aPosition"));
    rect.addVBO<GLTexture::UV>(texture->getUVs().data(),
                                 texture->getUVs().size() * sizeof(GLTools::Vertex),
                                 GL_FLOAT,
                                 getShader()->findAttr("aTexCoord"));
}

void GLViewSprite::draw(const PMatrix pMatrix, const MVMatrix mvMatrix) {
    getShader()->render(rect, [this, mvMatrix, pMatrix](){
        glUniformMatrix4fv(getShader()->findUniform("uMVMatrix"),1,false,mvMatrix);
        glUniformMatrix4fv(getShader()->findUniform("uPMatrix"),1,false,pMatrix);
        glUniform4f(getShader()->findUniform("uColor"),0,0,0,1);
        texture->bind(getShader()->findUniform("uTex"), 0);
    });
}


