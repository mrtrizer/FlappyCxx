#ifndef GWORLDVIEW_H
#define GWORLDVIEW_H


#ifdef QT_CORE_LIB
#include <GL/glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <vector>

#include "glshaderprogram.h"
#include "gltools.h"
#include "glattribarray.h"

class GObjCamera;
class GLShaderProgram;
class GWorldModel;
class IGViewFactory;

/// View in MVC terms.
class GWorldView {
public:
    typedef std::shared_ptr<GWorldModel> GWorldModelP;

    GWorldView(std::shared_ptr<IGViewFactory> factory):
        factory(factory)
    {}
    ~GWorldView();
    void setGWorldModel(GWorldModelP gWorldModel);
    void redraw();
    void resize(double width, double height);
    void init();

private:
    GWorldModelP gWorld;
    std::shared_ptr<IGViewFactory> factory;

    std::vector<GLfloat> getPMatrix(const std::shared_ptr<GObjCamera> &);

    int width = 100;
    int height = 100;
};

#endif // GWORLDVIEW_H
