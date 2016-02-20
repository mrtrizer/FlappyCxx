#include "gworldview.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "gworldmodel.h"
#include "gobjcamera.h"
#include "gviewshape.h"

using namespace std;

//TODO: gWorld to shared_ptr
GWorldView::GWorldView(const std::shared_ptr<GWorldModel> &gWorld):
    gWorld(gWorld) {
}

void GWorldView::init() {
    LOGI("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0, 0, 0, 0);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    CHECK_GL_ERROR;
}

GWorldView::~GWorldView() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE);
}

void GWorldView::resize(double width, double height) {
    glViewport(0, 0, width, height);
    gWorld->getActiveCamera()->setRatio(width / height);
}

void GWorldView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Calc ortho matrix, using GObjCamera
    auto pMatrix = gWorld->getActiveCamera()->getPMatrix();

    //TODO: Do it recursively
    auto root = gWorld->getRoot()->findChilds();
    for (std::shared_ptr<GObj> gObj: root) {

        //If it's a visible object
        auto view = std::dynamic_pointer_cast<GView>(gObj);
        if (view == nullptr)
            continue;

        //Get move matrix of the object
        auto mvMatrix = gObj->getPosAbsolute().getMvMatrix();

        view->draw(pMatrix.data(), mvMatrix.data());
    }
}
