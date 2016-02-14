#include "attribarray.h"

AttribArray::AttribArray(Size size): size(size) {
    glGenVertexArrays(1, &id);
}

void AttribArray::bind() const {
    glBindVertexArray(id);
}

void AttribArray::unbind() const {
    glBindVertexArray(0);
}
