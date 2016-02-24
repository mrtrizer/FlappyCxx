#ifndef GLVIEWFACTORY_H
#define GLVIEWFACTORY_H

#include "core/gviewfactory.h"

class GLViewFactory: public IGViewFactory {
public:
    virtual ~GLViewFactory() {}
    virtual GViewP getGViewSprite(const GPresenter & presenter) const override;
    virtual GViewP getGViewCircle(const GPresenter & presenter) const override;
    virtual GViewP getGViewRect(const GPresenter & presenter) const override;
    virtual std::shared_ptr<GLTexture> getGLTexture(std::string path) const = 0;
private:
    const int CIRCLE_VERTEX_CNT = 30;
};

#endif // GLVIEWFACTORY_H
