#ifndef GWORLDVIEW_H
#define GWORLDVIEW_H

#include <GL/glew.h>
#include <vector>

#include "shader.h"
#include "gltools.h"
#include "attribarray.h"

class GObjCamera;
class Shader;
class GWorldModel;

/// View in MVC terms.
class GWorldView {
public:
    GWorldView(GWorldModel &);
    ~GWorldView();
    void redraw();
    void resize(double width, double height);
    void init();

private:
    GWorldModel &gWorld;

    std::vector<GLfloat> getPMatrix(const std::shared_ptr<GObjCamera> &);
};

#endif // GWORLDVIEW_H
