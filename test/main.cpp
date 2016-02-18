#include <QTest>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <GL/glew.h>
#include <GL/glut.h>

#include <gworldview.h>
#include <gworldmodel.h>
#include <gobjcircle.h>
#include <gobjcamera.h>
#include <gobjrect.h>

#include "test_gobj.h"
#include "test_tools.h"

std::shared_ptr<GWorldModel> gWorldModel;
std::shared_ptr<GWorldView> gWorldView;

void render() {
    gWorldView->redraw();
    glutSwapBuffers();
    glutPostRedisplay();
    gWorldModel->run(); //only for test
}

void resizeWindow(int width, int height) {
    gWorldView->resize(width, height);
}

int main(int argc, char** argv)
{
    gWorldModel = std::make_shared<GWorldFlappy>();
    gWorldView = std::make_shared<GWorldView>(gWorldModel);

    int status = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple shaders");
    glewInit();

    //Fill scene with objects
    auto gObjSubContainer1 = gWorldModel->getRoot()->ADD_CHILD(GObj,POS(0,0,0));
    auto gObjSubContainer2 = gObjSubContainer1->ADD_CHILD(GObj,POS(-15,0,0));
    gObjSubContainer1->ADD_CHILD(GObjRect,20,20,POS(-10,-10,0));
    gObjSubContainer2->ADD_CHILD(GObjCircle,4,POS(-20,-20,0));
    gObjSubContainer2->ADD_CHILD(GObjCircle,6,POS(20,-20,0));
    gObjSubContainer2->ADD_CHILD(GObjCircle,8,POS(-20,20,0));
    gObjSubContainer2->ADD_CHILD(GObjCircle,10,POS(20,20,0));
    auto gObjCamera = std::make_shared<GObjCamera>(100,1.0,GObj::Pos({0,0,0}));
    gWorldModel->getRoot()->addChild<GObjCamera>(gObjCamera);
    gWorldModel->setActiveCamera(gObjCamera);

    gWorldView->init();

    const auto RUN_TEST = [&status, argc, argv] (QObject * obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };

    RUN_TEST(new Test_GObj());
    RUN_TEST(new Test_Tools());

    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutMainLoop();

    return status;
}
