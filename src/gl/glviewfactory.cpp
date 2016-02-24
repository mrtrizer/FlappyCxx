#include "glviewfactory.h"
#include "glviewshape.h"
#include "glviewsprite.h"

GViewFactory::GViewP GLViewFactory::getGViewSprite(const GPresenter &presenter) const {
    auto presenterSprite = dynamic_cast<const GPresenterSprite &>(presenter);
    return std::make_shared<GLViewSprite>(getGLTexture(presenterSprite.getPath()),
                                         presenterSprite.getWidth(),
                                         presenterSprite.getHeight());
}

GViewFactory::GViewP GLViewFactory::getGViewCircle(const GPresenter &presenter) const {
    auto presenterCircle = dynamic_cast<const GPresenterCircle &>(presenter);
    return std::make_shared<GViewCircle>(CIRCLE_VERTEX_CNT, presenterCircle.getR_());
}

GViewFactory::GViewP GLViewFactory::getGViewRect(const GPresenter &presenter) const {
    auto presenterRect = dynamic_cast<const GPresenterRect &>(presenter);
    return std::make_shared<GViewRect>(presenterRect.getWidth(), presenterRect.getHeight());
}
