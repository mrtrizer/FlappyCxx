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

GWorldFlappy gWorldModel;
GWorldView gWorldView(gWorldModel);

void render() {
    gWorldView.redraw();
    glutSwapBuffers();
    glutPostRedisplay();
    gWorldModel.run(); //only for test
}

void resizeWindow(int width, int height) {
    gWorldView.resize(width, height);
}

int main(int argc, char** argv)
{
   int status = 0;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Simple shaders");
   glewInit();

   auto gObjSubContainer1 = gWorldModel.getRoot()->addChild<GObj>(std::make_shared<GObj>(GObj::Pos({5,0,0})));
   auto gObjSubContainer2 = gObjSubContainer1->addChild<GObj>(std::make_shared<GObj>(GObj::Pos({0,0,0})));
   gObjSubContainer2->addChild<GObjRect>(std::make_shared<GObjRect>(10,10,GObj::Pos({-5,-5,0})));
   gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(2,GObj::Pos({-20,-20,0})));
   gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(4,GObj::Pos({20,-20,0})));
   gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(6,GObj::Pos({-20,20,0})));
   gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(8,GObj::Pos({20,20,0})));
   auto gObjCamera = std::make_shared<GObjCamera>(100,1.0,GObj::Pos({10,0,0}));
   gWorldModel.getRoot()->addChild<GObjCamera>(gObjCamera);
   gWorldModel.setActiveCamera(gObjCamera);

   gWorldView.init();

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
