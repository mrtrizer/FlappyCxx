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
    typedef int Width;
    typedef int Height;
    GWorldView(GWorldModel &);
    ~GWorldView();
    void redraw();
    void resize(Width, Height);

private:
    Width width;
    Height height;
    GWorldModel &gWorld;

    std::vector<GLfloat> getPMatrix(const std::shared_ptr<GObjCamera> & gObjCamera);
};

#endif // GWORLDVIEW_H
