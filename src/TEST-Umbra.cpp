//============================================================================
// Name        : TEST-Umbra.cpp
// Author      : UnSchtalch
// Version     :
// Copyright   : Free to use
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
using namespace std;

void
init(void)

{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

int
main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Umbra");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
