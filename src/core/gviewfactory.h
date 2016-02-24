#ifndef GVIEWFACTORY_H
#define GVIEWFACTORY_H

#include <memory>
#include <string>

#include "gpresenter.h"

class GView;
class GLTexture;

class IGViewFactory
{
public:
    typedef std::shared_ptr<GView> GViewP;

    virtual ~IGViewFactory() {}
    virtual GViewP getGViewSprite(const GPresenter &) const = 0;
    virtual GViewP getGViewCircle(const GPresenter & ) const = 0;
    virtual GViewP getGViewRect(const GPresenter & ) const = 0;
};

#endif // GVIEWFACTORY_H
