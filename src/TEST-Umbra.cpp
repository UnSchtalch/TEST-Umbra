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

GLubyte *textureImage;  //bad idea, just for experiment;

GLuint png_texture(char *filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int height, width;
	bool hasAlpha;
	bool success = false;
	success = loadPNGImage(filename, width, height, hasAlpha, &textureImage);
	if (!success)
	{
	//	cout << "fail!" << endl;
		return 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, textureImage);
	return tex;
}

GLuint textnum;

void display(void)
{
	textnum = png_texture("./1.png");
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, textnum);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0, 0.0);  glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 1.0);
	}
	glEnd();

	glFlush();

}

void init(void)

{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_BLEND);  //transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	cout<<glGetError()<<endl;
	glEnable(GL_TEXTURE_2D);
	//cout<<glGetError()<<endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.1, 1.1, -0.1, 1.1);

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
