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
GWorldView::GWorldView(GWorldModel &gWorld):
    gWorld(gWorld) {
}

void GWorldView::init() {
    LOGI("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0, 0, 0, 0);
    glEnable(GL_MULTISAMPLE);

    CHECK_GL_ERROR;
}

GWorldView::~GWorldView() {
    glDisable(GL_MULTISAMPLE);
}

void GWorldView::resize(double width, double height) {
    glViewport(0, 0, width, height);
    gWorld.getActiveCamera()->setRatio(width / height);
}

void GWorldView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Calc ortho matrix, using GObjCamera
    auto rect = gWorld.getActiveCamera()->getRect();
    static const float near = 0.0f;
    static const float far = 100.0f;

    GLfloat pMatrix[] = {
        2.0f / (rect.x2 - rect.x1), 0, 0, (rect.x2 + rect.x1) / (rect.x2 - rect.x1),
        0, 2.0f / (rect.y1 - rect.y2), 0, (rect.y1 + rect.y2) / (rect.y1 - rect.y2),
        0, 0, -2.0f / (far - near), (far + near) / (far - near),
        0, 0, 0, 1.0f
    };

    //For all children recursively
    auto root = gWorld.getRoot()->getChildsR();
    for (std::shared_ptr<GObj> gObj: root) {

        //If it's a visible object
        auto view = std::dynamic_pointer_cast<GView>(gObj);
        if (view == nullptr)
            continue;

        GObj::Pos pos = gObj->getPosAbsolute();
        GLfloat mvMatrix[] = {
            1.0f, 0, 0, pos.x,
            0, 1.0f, 0, pos.y,
            0, 0, 1.0f, pos.z,
            0, 0, 0, 1.0f
        };

        view->draw(pMatrix, mvMatrix);
    }
}
