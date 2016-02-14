#ifndef ATTRIBARRAY_H
#define ATTRIBARRAY_H

#include <GL/glew.h>
#include <cassert>

#include "gltools.h"

class AttribArray {
public:
    typedef int Size;
    explicit AttribArray(Size size = -1);
    ~AttribArray();

    void bind() const;
    void unbind() const;

    inline Size getSize() const {return size;}

    template<typename ItemType>
    void addVBO(const ItemType * buf, int bufSize, int itemType, GLint attr) {
        VBO vbo;
        int count = bufSize / sizeof(ItemType);
        if ((count < size) || (size == -1))
            size = count;
        glBindVertexArray(id);
        checkOpenGLerror();
        glGenBuffers(1, &vbo);
        checkOpenGLerror();
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        checkOpenGLerror();
        glBufferData(GL_ARRAY_BUFFER, bufSize, buf, GL_STATIC_DRAW);
        checkOpenGLerror();
        assert(itemType == GL_FLOAT); //TODO: Now only GL_FLOAT items supported
        glVertexAttribPointer(attr, sizeof(ItemType) / 4, itemType, GL_FALSE, 0, 0);
        checkOpenGLerror();
        glEnableVertexAttribArray(attr);
        checkOpenGLerror();
        glBindVertexArray(0);
    }

private:
    typedef GLuint VBO;
    typedef GLuint Id;
    Id id;
    Size size;
};

#endif // ATTRIBARRAY_H
