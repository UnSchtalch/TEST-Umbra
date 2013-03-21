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

bool loadPNGImage(char* name, int &outWidth, int &outHeght, bool &outHasAlpha,
		GLubyte **outData);

GLubyte *textureImage;//bad idea, just for experiment;

void init(void)

{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glEnable(GL_BLEND);//transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//mock-up code
	int height, width;
	bool hasAlpha;
	char filename[]="1.png";
	bool success = false;
	success = loadPNGImage(filename, width, height, hasAlpha, &textureImage);
	if (!success)
	{
		cout<<"fail!"<<endl;
		return;
	}

	cout<<"win!"<<endl;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage2D(GL_TEXTURE_2D,0,hasAlpha ? 4:3, width, height,0,hasAlpha ? GLUT_RGBA:GL_RGB, GL_UNSIGNED_BYTE, textureImage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0,0.0,-3.6);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0,0.0);
	glVertex3d(-2.0,-1.0, 0.0);

	glTexCoord2f(0.0,1.0);
	glVertex3d(-2.0,1.0, 0.0);

	glTexCoord2f(1.0,1.0);
	glVertex3d(0.0,1.0, 0.0);

	glTexCoord2f(1.0,0.0);
	glVertex3d(0.0,-1.0, 0.0);

	glEnd();
	glutSwapBuffers();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Umbra");
	//glutFullScreen(); -- ok, i can do this, once i find out key processing events`
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
