#ifndef ATTRIBARRAY_H
#define ATTRIBARRAY_H

#include <GL/glew.h>
#include <cassert>

#include "gltools.h"

//TODO: Rename to GLAttribArray
/// Contains VBOs, draw method and item count for drawArrays().
/// Kinda mesh object.
/// @see Shader
class AttribArray {
public:
    typedef int Size;
    typedef unsigned int Method;

    explicit AttribArray(Method = GL_TRIANGLES, Size = -1);
    ~AttribArray();

    void bind() const;
    void unbind() const;

    inline Size getSize() const {return size;}
    inline Method getMethod() const {return method;}

    template<typename ItemType>
    void addVBO(const ItemType * buf, int bufSize, int itemType, GLint attr) {
        VBO vbo;
        int count = bufSize / sizeof(ItemType);
        if ((count < size) || (size == -1)) //I keep min count of attrib items to use in drawArrays
            size = count;
        glBindVertexArray(id);
        CHECK_GL_ERROR;
        glGenBuffers(1, &vbo);
        CHECK_GL_ERROR;
        vboBufs.push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        CHECK_GL_ERROR;
        glBufferData(GL_ARRAY_BUFFER, bufSize, buf, GL_STATIC_DRAW);
        CHECK_GL_ERROR;
        assert(itemType == GL_FLOAT); //TODO: Now only GL_FLOAT items supported
        glVertexAttribPointer(attr, sizeof(ItemType) / 4, itemType, GL_FALSE, 0, 0);
        CHECK_GL_ERROR;
        glEnableVertexAttribArray(attr);
        CHECK_GL_ERROR;
        glBindVertexArray(0);
    }

private:
    typedef GLuint VBO;
    typedef std::vector<VBO> VBOBufs;
    typedef GLuint Id;
    Id id;
    Size size;
    VBOBufs vboBufs; //need only to cleanup vbos
    Method method;
};

#endif // ATTRIBARRAY_H
