#ifndef GLWORLDVIEW_H
#define GLWORLDVIEW_H

#include <vector>

#include "core/gworldview.h"

class GLViewFactory;

/// View in MVC terms.
class GLWorldView : public GWorldView {
public:
    GLWorldView(const std::shared_ptr<GLViewFactory> & factory):
        factory(factory)
    {}
    virtual ~GLWorldView();
    void redraw() override;
    void init() override;
protected:
    void updateViewPort() override;
private:
    std::shared_ptr<GLViewFactory> factory;
};

#endif // GLWORLDVIEW_H
