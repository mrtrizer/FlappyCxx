#ifndef GWORLDVIEW_H
#define GWORLDVIEW_H

#include <memory>

#include "gviewfactory.h"

class GWorldModel;
class IGViewFactory;

class GWorldView {
public:
    typedef std::shared_ptr<GWorldModel> GWorldModelP;

    GWorldView(const std::shared_ptr<IGViewFactory> & factory):
        factory(factory)
    {}
    virtual ~GWorldView(){}
    void setGWorldModel(GWorldModelP gWorldModel);
    virtual void redraw() = 0;
    void resize(int lastWidth, int lastHeight);
    virtual void init() = 0;

protected:
    int lastWidth = 100;
    int lastHeight = 100;
    GWorldModelP gWorld;
    std::shared_ptr<IGViewFactory> factory;

    virtual void updateViewPort() = 0;
};

#endif // GWORLDVIEW_H
