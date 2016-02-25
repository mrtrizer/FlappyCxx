#include <QTest>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <GL/glew.h>
#include <GL/glut.h>

#include <gl/glworldview.h>
#include <core/gworldmodel.h>
#include <shapes/gobjcircle.h>
#include <core/gobjcamera.h>
#include <shapes/gobjrect.h>
#include <world.h>
#include <ctrl.h>

#include "test_gobj.h"
#include "glviewfactoryqt.h"

std::shared_ptr<GLWorldView> gWorldView;
std::shared_ptr<Ctrl> flappyCtrl;

void render() {
    gWorldView->redraw();
    glutSwapBuffers();
    glutPostRedisplay();
    flappyCtrl->step(); //only for test
}

void resizeWindow(int width, int height) {
    gWorldView = std::make_shared<GLWorldView>(std::make_shared<GLViewFactoryQt>("../res/"));
    flappyCtrl->setView(gWorldView);
    gWorldView->resize(width, height);
}

void mouseFunc(int button, int state,
               int x, int y) {
    (void)button;
    (void)state;
    flappyCtrl->mouseClick(x,y);
}

void passiveMotionFunc(int x, int y) {
    flappyCtrl->mouseMove(x,y);
}

int main(int argc, char** argv)
{
    flappyCtrl = std::make_shared<Ctrl>();

    int status = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(400, 600);
    glutCreateWindow("FlappyCxx");
    glewInit();

    flappyCtrl->init();

    const auto RUN_TEST = [&status, argc, argv] (QObject * obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };

    RUN_TEST(new Test_GObj());

    glutMouseFunc(mouseFunc);
    glutPassiveMotionFunc(passiveMotionFunc);
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutMainLoop();

    return status;
}
