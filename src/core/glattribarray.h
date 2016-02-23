#ifndef GL_ATTRIBARRAY_H
#define GL_ATTRIBARRAY_H

#include <vector>

#include "gltools.h"

/// Contains VBOs, draw method and item count for drawArrays().
/// Kinda mesh object.
/// @see Shader
class GLAttribArray {
public:
    typedef int Size;
    typedef unsigned int Method;

    explicit GLAttribArray(Method = GL_TRIANGLES, Size = -1);
    ~GLAttribArray();

    void bind() const;
    void unbind() const;

    inline Size getSize() const {return size;}
    inline Method getMethod() const {return method;}

    template<typename ItemType>
    void addVBO(const ItemType * buf, int bufSize, int itemType, GLint attr) {
        VBO vbo;
        vbo.componentCount = sizeof(ItemType) / 4;
        vbo.itemType = itemType;
        vbo.attr = attr;
        int count = bufSize / sizeof(ItemType);
        if ((count < size) || (size == -1)) //I keep min count of attrib items to use in drawArrays
            size = count;
        glGenBuffers(1, &vbo.id);
        CHECK_GL_ERROR;
        vboBufs.push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
        CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER, bufSize, buf, GL_STATIC_DRAW);
        CHECK_GL_ERROR;
        if (itemType != GL_FLOAT)
            std::runtime_error("Now only GL_FLOAT items supported!");
    }

private:
    struct VBO {
        int itemType;
        int componentCount;
        GLint attr;
        GLuint id;
    };

    typedef std::vector<VBO> VBOBufs;
    typedef GLuint Id;
    Id id;
    Size size;
    VBOBufs vboBufs; //need only to cleanup vbos
    Method method;
};

#endif // GL_ATTRIBARRAY_H
