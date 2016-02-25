#ifndef GLVIEWFACTORY_H
#define GLVIEWFACTORY_H

#include "core/gviewfactory.h"
#include <map>

class GLViewFactory: public GViewFactory {
public:
    virtual ~GLViewFactory() {}
    virtual GViewP getGViewSprite(const GPresenter & presenter) const override;
    virtual GViewP getGViewCircle(const GPresenter & presenter) const override;
    virtual GViewP getGViewRect(const GPresenter & presenter) const override;
    virtual std::shared_ptr<GLTexture> getGLTexture(std::string path) const = 0;
private:
    typedef std::map<std::string,std::shared_ptr<GLTexture>> TextureMap;

    const int CIRCLE_VERTEX_CNT = 30;
    mutable TextureMap textureMap;
};

#endif // GLVIEWFACTORY_H