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

#include "test_gobj.h"

std::shared_ptr<FlappyWorld> flappyWorld;
std::shared_ptr<GWorldView> gWorldView;

void render() {
    gWorldView->redraw();
    glutSwapBuffers();
    glutPostRedisplay();
    flappyWorld->run(); //only for test
}

void resizeWindow(int width, int height) {
    gWorldView->resize(width, height);
}

void mouseFunc(int button, int state,
               int x, int y) {
    flappyWorld->flap();
}

int main(int argc, char** argv)
{
    flappyWorld = std::make_shared<FlappyWorld>();
    gWorldView = std::make_shared<GWorldView>(flappyWorld);

    int status = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple shaders");
    glewInit();

    gWorldView->init();
    flappyWorld->init();

    const auto RUN_TEST = [&status, argc, argv] (QObject * obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };

    RUN_TEST(new Test_GObj());

    glutMouseFunc(mouseFunc);
    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutMainLoop();

    return status;
}
