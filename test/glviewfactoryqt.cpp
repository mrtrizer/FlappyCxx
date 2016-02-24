#include "glviewfactoryqt.h"

GLViewFactoryQt::GLViewFactoryQt()
{

}

std::shared_ptr<GLTexture> GLViewFactoryQt::getGLTexture(std::string path) const {
    QImage image(QString("../test/") + QString::fromStdString(path) + QString(".png"));
    const uchar * bits = image.bits();
    auto result = std::make_shared<GLTexture>(bits, image.width(), image.height());
    return result;
}
