#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "gview.h"
#include "gworld.h"
#include "gobjcircle.h"

GView * view;
GWorld gWorld;

void render() {
    view->redraw();
    glutSwapBuffers();
}

void resizeWindow(int width, int height) {
    view->resize(width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
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

    gWorld.getObjTree().addChild(GObjCircle(1,10));
    view = new GView(gWorld);

    glutReshapeFunc(resizeWindow);
    glutDisplayFunc(render);
    glutMainLoop();

    delete view;
    return 0;
}
