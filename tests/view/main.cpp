#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GL/glut.h>

#include "gworldview.h"
#include "gworldmodel.h"
#include "gobjcircle.h"
#include "gobjcamera.h"

GWorldView * view;
GWorldFlappy gWorld;

void render() {
    view->redraw();
    glutSwapBuffers();
    glutPostRedisplay();
    gWorld.run();
}

void resizeWindow(int width, int height) {
    view->resize(width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple shaders");

    GLenum glew_status = glewInit();
    if(GLEW_OK != glew_status)
    {
      std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
      return 1;
    }

    if(!GLEW_VERSION_2_0)
     {
      std::cout << "No support for OpenGL 2.0 found\n";
      return 1;
    }

    auto gObjSubContainer1 = gWorld.getRoot()->addChild<GObjContainer>(std::make_shared<GObjContainer>(GObj::Pos({5,0,0})));
    auto gObjSubContainer2 = gObjSubContainer1->addChild<GObjContainer>(std::make_shared<GObjContainer>(GObj::Pos({0,0,0})));
    gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(2,GObj::Pos({-5,-5,0})));
    gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(4,GObj::Pos({5,-5,0})));
    gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(6,GObj::Pos({-5,5,0})));
    gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(8,GObj::Pos({5,5,0})));
    gWorld.getRoot()->addChild<GObjCamera>(std::make_shared<GObjCamera>(20,GObj::Pos({10,0,0})));
    view = new GWorldView(gWorld);

    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutMainLoop();

    delete view;
    return 0;
}
