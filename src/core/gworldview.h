#ifndef GWORLDVIEW_H
#define GWORLDVIEW_H

#include <memory>

#include "gviewfactory.h"

class GWorldModel;
class GViewFactory;

/// @brief Abstract base for View implementations in MVC terms.
/// @details Holds a pointer to GWorldModel.
class GWorldView {
public:
    typedef std::shared_ptr<GWorldModel> GWorldModelP;

    virtual ~GWorldView(){}
    void setGWorldModel(GWorldModelP gWorldModel);
    virtual void redraw() = 0;
    void resize(int width, int height);
    virtual void init() = 0;
    void updateSize();

protected:
    GWorldModelP getGWorld() { return gWorld; }

private:
    int width = 1;
    int height = 1;
    GWorldModelP gWorld;

    virtual void updateViewPort(int width, int height) = 0;
};

#endif // GWORLDVIEW_H
