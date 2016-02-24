#ifndef GLWORLDVIEW_H
#define GLWORLDVIEW_H

#ifdef QT_CORE_LIB
#include <GL/glew.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <vector>

#include "core/gworldview.h"

/// View in MVC terms.
class GLWorldView : public GWorldView {
public:
    using GWorldView::GWorldView;
    virtual ~GLWorldView();
    void redraw() override;
    void init() override;
protected:
    void updateViewPort() override;
};

#endif // GLWORLDVIEW_H
