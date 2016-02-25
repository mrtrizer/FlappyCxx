#include "gpresenter.h"
#include "gviewfactory.h"

std::shared_ptr<GView> GPresenter::getGView(const GViewFactory &factory) {
    if (gView == nullptr)
        gView = makeGView(factory);
    return gView;
}

void GPresenter::cleanGView(){
    gView = nullptr;
}

std::shared_ptr<GView> GPresenterSprite::makeGView(const GViewFactory &factory) {
    return factory.getGViewSprite(*this);
}

std::shared_ptr<GView> GPresenterCircle::makeGView(const GViewFactory &factory) {
    return factory.getGViewCircle(*this);
}

std::shared_ptr<GView> GPresenterRect::makeGView(const GViewFactory &factory) {
    return factory.getGViewRect(*this);
}
