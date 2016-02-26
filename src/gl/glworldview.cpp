#include "glworldview.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glshaderprogram.h"
#include "core/gworldmodel.h"
#include "core/gobjcamera.h"
#include "core/gview.h"
#include "core/gpresenter.h"
#include "glshaderprogram.h"
#include "gltools.h"
#include "glattribarray.h"
#include "glviewfactory.h"

using namespace std;

void GLWorldView::init() {
    LOGI("OpenGL Version: %s\n", glGetString(GL_VERSION));
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_BLEND);
    CHECK_GL_ERROR;
    resize(lastWidth, lastHeight);
}

GLWorldView::~GLWorldView() {
    glDisable(GL_DEPTH_TEST);
    //clean presenters
    auto root = gWorld->getRoot()->findChilds();
    for (std::shared_ptr<GObj> gObj: root) {
        //If it's a visible object
        auto presenter = std::dynamic_pointer_cast<GPresenter>(gObj);
        if (presenter == nullptr)
            continue;
        presenter->cleanGView();
    }
}

void GLWorldView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gWorld == nullptr)
        return;

    //Calc ortho matrix, using GObjCamera
    auto pMatrix = gWorld->getActiveCamera()->getPMatrix();

    //TODO: Optimize GObj::getPosAbsolute()
    GObj::GObjPList objects = gWorld->getRoot()->findChilds();
    objects.sort([](const GObj::GObjP & first, const GObj::GObjP & second) {
        return first->getStaticZ() < second->getStaticZ();
    });

    for (auto gObj: objects) {
        auto presenter = std::dynamic_pointer_cast<GPresenter>(gObj);
        if (presenter == nullptr)
            continue;

        //Get move matrix of the object
        auto mvMatrix = gObj->getAPos().getMvMatrix();

        presenter->getGView(*factory)->redraw(pMatrix.data(), mvMatrix.data());
    }

}

void GLWorldView::updateViewPort() {
    glViewport(0, 0, lastWidth, lastHeight);
}
