#include "attribarray.h"

///@param size Count of items for glDrawArrays()
AttribArray::AttribArray(Method method, Size size):
    size(size),
    method(method){
    glGenVertexArrays(1, &id);
}

AttribArray::~AttribArray() {
    //TODO: Do I need unbind VBOs? How to do it properly?
    glDeleteVertexArrays(1,&id);
    glDeleteBuffers(vboBufs.size(),vboBufs.data());
}

void AttribArray::bind() const {
    glBindVertexArray(id);
}

void AttribArray::unbind() const {
    glBindVertexArray(0);
}
