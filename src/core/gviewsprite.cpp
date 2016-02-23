#include "gviewsprite.h"

static const char gVertexShader[] =
    "attribute vec2 aPosition;\n"
    "attribute vec2 aTexCoord;\n"
    "uniform mat4 uMVMatrix;\n"
    "uniform mat4 uPMatrix;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "   vTexCoord = aTexCoord;"
    "   gl_Position = uPMatrix * uMVMatrix * vec4(aPosition,0,1);\n"
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;\n"
    "uniform sampler2D uTex;\n"
    "uniform vec4 uColor;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "   gl_FragColor = texture(uTex,vTexCoord);\n"
    "}\n";

GViewSprite::GViewSprite(float width, float height, const GLTexture & texture) :
    shader(gVertexShader, gFragmentShader),
    rect(GL_TRIANGLE_STRIP),
    texture(texture) {

    std::vector<GLTools::Vertex> vertexList({
                                                {0,0},
                                                {0,height},
                                                {width,0},
                                                {width,height}
                                            });
    std::vector<GLTools::Vertex> textureCoordList({{0,0},{0,1},{1,0},{1,1}});
    rect.addVBO<GLTools::Vertex>(vertexList.data(),
                                 vertexList.size() * sizeof(GLTools::Vertex),
                                 GL_FLOAT,
                                 shader.findAttr("aPosition"));
    rect.addVBO<GLTools::Vertex>(textureCoordList.data(),
                                 textureCoordList.size() * sizeof(GLTools::Vertex),
                                 GL_FLOAT,
                                 shader.findAttr("aTexCoord"));
}

void GViewSprite::draw(const PMatrix pMatrix, const MVMatrix mvMatrix) {
    shader.render(rect, [this, mvMatrix, pMatrix](){
        glUniformMatrix4fv(shader.findUniform("uMVMatrix"),1,false,mvMatrix);
        glUniformMatrix4fv(shader.findUniform("uPMatrix"),1,false,pMatrix);
        glUniform4f(shader.findUniform("uColor"),0,0,0,1);
        texture.bind(shader.findUniform("uTex"), 0);
    });
}


