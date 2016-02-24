#include "gpresenter.h"
#include "gviewfactory.h"

std::shared_ptr<GView> GPresenter::getGView(const IGViewFactory &factory) {
    if (gView == nullptr)
        gView = factory.getGViewSprite(*this);
    return gView;
}
