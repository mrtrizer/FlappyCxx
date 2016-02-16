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



GWorldView::GWorldView(GWorldModel &gWorld):
    gWorld(gWorld) {

    LOGI("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0, 0, 0, 0);
    glEnable(GL_MULTISAMPLE);


    CHECK_GL_ERROR;
}

GWorldView::~GWorldView() {
    glDisable(GL_MULTISAMPLE);
}

void GWorldView::resize(Width width, Height height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

void GWorldView::redraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Find GObjCamera object
    std::shared_ptr<GObj> gObj = nullptr;
    try {
        gObj = gWorld.getRoot()->findChildR([](const GObj::GObjP & i) {
            return std::dynamic_pointer_cast<GObjCamera>(i) != nullptr;
        });
    } catch (GObjContainer::cant_find_child &) {
        throw std::runtime_error("Can't find camera object. Add GObjCamera object to your tree.");
    }

    auto gObjCamera = std::dynamic_pointer_cast<GObjCamera>(gObj);

    //Calc ortho matrix, using GObjCamera
    const float offset = gObjCamera->getHeight() / 2.0;
    GObj::Pos pos = gObjCamera->getPosAbsolute();
    const float left = -offset * width / height - pos.x;
    const float right = offset * width / height - pos.x;
    const float bottom = -offset - pos.y;
    const float top = offset - pos.y;
    static const float near = 0.0f;
    static const float far = 100.0f;

    GLfloat pMatrix[] = {
        2.0f / (right - left), 0, 0, (right + left) / (right - left),
        0, 2.0f / (top - bottom), 0, (top + bottom) / (top - bottom),
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
