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
    void resize(int lastWidth, int lastHeight);
    virtual void init() = 0;

protected:
    //TODO: Move to private, add getters
    int lastWidth = 100;
    int lastHeight = 100;
    GWorldModelP gWorld;

    virtual void updateViewPort() = 0;
};

#endif // GWORLDVIEW_H
