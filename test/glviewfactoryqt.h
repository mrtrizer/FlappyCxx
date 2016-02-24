#ifndef GLVIEWFACTORYQT_H
#define GLVIEWFACTORYQT_H

#include <QImage>

#include <core/gviewfactory.h>

class GLViewFactoryQt :public GLViewFactory
{
public:
    GLViewFactoryQt();
    virtual std::shared_ptr<GLTexture> getGLTexture(std::string path) const override;
};

#endif // GLVIEWFACTORYQT_H
