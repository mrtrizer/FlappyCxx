#include "gpresenter.h"
#include "gviewfactory.h"

std::shared_ptr<GView> GPresenter::getGView(const IGViewFactory &factory) {
    if (gView == nullptr)
        gView = makeGView(factory);
    return gView;
}

std::shared_ptr<GView> GPresenterSprite::makeGView(const IGViewFactory &factory) {
    return factory.getGViewSprite(*this);
}

std::shared_ptr<GView> GPresenterCircle::makeGView(const IGViewFactory &factory) {
    return factory.getGViewCircle(*this);
}

std::shared_ptr<GView> GPresenterRect::makeGView(const IGViewFactory &factory) {
    return factory.getGViewRect(*this);
}
