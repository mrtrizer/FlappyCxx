#include <QTest>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <GL/glew.h>
#include <GL/glut.h>

#include <core/gworldview.h>
#include <core/gworldmodel.h>
#include <shapes/gobjcircle.h>
#include <core/gobjcamera.h>
#include <shapes/gobjrect.h>
#include <flappyworld.h>
#include <flappyctrl.h>

#include "test_gobj.h"

FlappyCtrl flappyCtrl;

void render() {
    flappyCtrl.glRedraw();
    glutSwapBuffers();
    glutPostRedisplay();
    flappyCtrl.step(); //only for test
}

void resizeWindow(int width, int height) {
    flappyCtrl.resize(width, height);
}

void mouseFunc(int button, int state,
               int x, int y) {
    (void)button;
    (void)state;
    flappyCtrl.mouseClick(x,y);
}

void passiveMotionFunc(int x, int y) {
    flappyCtrl.mouseMove(x,y);
}

int main(int argc, char** argv)
{
    int status = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple shaders");
    glewInit();

    flappyCtrl.init();

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
