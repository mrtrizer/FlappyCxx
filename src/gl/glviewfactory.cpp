#include "glviewfactory.h"
#include "gviewshape.h"
#include "gviewsprite.h"

IGViewFactory::GViewP GLViewFactory::getGViewSprite(const GPresenter &presenter) const {
    auto presenterSprite = dynamic_cast<const GPresenterSprite &>(presenter);
    return std::make_shared<GViewSprite>(getGLTexture(presenterSprite.getPath()),
                                         presenterSprite.getWidth(),
                                         presenterSprite.getHeight());
}

IGViewFactory::GViewP GLViewFactory::getGViewCircle(const GPresenter &presenter) const {
    auto presenterCircle = dynamic_cast<const GPresenterCircle &>(presenter);
    return std::make_shared<GViewCircle>(CIRCLE_VERTEX_CNT, presenterCircle.getR_());
}

IGViewFactory::GViewP GLViewFactory::getGViewRect(const GPresenter &presenter) const {
    auto presenterRect = dynamic_cast<const GPresenterRect &>(presenter);
    return std::make_shared<GViewRect>(presenterRect.getWidth(), presenterRect.getHeight());
}
