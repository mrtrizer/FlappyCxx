#ifndef GWORLDVIEW_H
#define GWORLDVIEW_H


#ifdef QT_CORE_LIB
#include <GL/glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
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
    GWorldView(const std::shared_ptr<GWorldModel> &);
    ~GWorldView();
    void redraw();
    void resize(double width, double height);
    void init();

private:
    std::shared_ptr<GWorldModel> gWorld;

    std::vector<GLfloat> getPMatrix(const std::shared_ptr<GObjCamera> &);
};

#endif // GWORLDVIEW_H
