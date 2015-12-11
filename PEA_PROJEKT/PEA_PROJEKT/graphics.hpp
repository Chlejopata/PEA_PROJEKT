#ifndef HEADERS_GRAPHICS_HPP_
#define HEADERS_GRAPHICS_HPP_

#include "stdafx.h"

#include <gl/gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>

GLdouble dimensions = 200.0;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	glutSwapBuffers();
}

void changeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

	if (horizontal <= vertical)
		glOrtho(-dimensions, dimensions, -dimensions / AspectRatio, dimensions / AspectRatio, dimensions, -dimensions);

	else
		glOrtho(-dimensions*AspectRatio, dimensions*AspectRatio, -dimensions, dimensions, dimensions, -dimensions);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initializeGraphics()
{
	stringstream title;
	title << "Projekt PEA";
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(title.str().c_str());

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(animation);

	//glutKeyboardFunc(keyboard);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

#endif