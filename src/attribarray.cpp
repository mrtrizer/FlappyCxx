#include "attribarray.h"

AttribArray::AttribArray(Size size): size(size) {
    glGenVertexArrays(1, &id);
}

AttribArray::~AttribArray() {
    //TODO: Do I need unbind VBOs?
    glDeleteVertexArrays(1,&id);
    glDeleteBuffers(vboBufs.size(),vboBufs.data());
}

void AttribArray::bind() const {
    glBindVertexArray(id);
}

void AttribArray::unbind() const {
    glBindVertexArray(0);
}
