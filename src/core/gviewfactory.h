#ifndef GVIEWFACTORY_H
#define GVIEWFACTORY_H

#include <memory>
#include <string>

#include "gviewsprite.h"
#include "gviewshape.h"
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

class GLViewFactory: public IGViewFactory {
public:
    virtual ~GLViewFactory() {}
    virtual GViewP getGViewSprite(const GPresenter & presenter) const override {
        auto presenterSprite = dynamic_cast<const GPresenterSprite &>(presenter);
        return std::make_shared<GViewSprite>(getGLTexture(presenterSprite.getPath()),
                                             presenterSprite.getWidth(),
                                             presenterSprite.getHeight());
    }
    virtual GViewP getGViewCircle(const GPresenter & presenter) const override {
        auto presenterCircle = dynamic_cast<const GPresenterCircle &>(presenter);
        return std::make_shared<GViewCircle>(CIRCLE_VERTEX_CNT, presenterCircle.getR_());
    }
    virtual GViewP getGViewRect(const GPresenter & presenter) const override {
        auto presenterRect = dynamic_cast<const GPresenterRect &>(presenter);
        return std::make_shared<GViewRect>(presenterRect.getWidth(), presenterRect.getHeight());
    }
    virtual std::shared_ptr<GLTexture> getGLTexture(std::string path) const = 0;
private:
    const int CIRCLE_VERTEX_CNT = 30;
};

#endif // GVIEWFACTORY_H
