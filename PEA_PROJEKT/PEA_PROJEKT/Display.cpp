#ifndef _WIN64
#include "Display.h"

MatrixGraph* Display::mg = nullptr;
GLdouble Display::dimensions = 200.0;
vector<DisplayVertex> Display::vertices;
vector<DisplayEdge> Display::edges;
bool Display::parsed = false;

Display::Display()
{
}

Display::~Display()
{
}

void Display::renderScene(void)
{
	if (Display::mg && Display::mg->getVertexNumber())
	{
		if (!parsed)
		{
			for (uint i = 0; i < mg->getVertexNumber(); i++)
			{
				vertices.emplace_back(i);
			}
			parsed = true;
		}
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Czyszczenie okna aktualnym kolorem czyszcz¹cym
		glLoadIdentity();
		// Czyszczenie macierzy bie¿¹cej

		for (auto v : vertices)
		{
			v.draw();
		}

		glutSwapBuffers();
	}
	
}

void Display::changeSize(GLsizei horizontal, GLsizei vertical)
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

void Display::initializeGraphics(MatrixGraph *mg)
{
	Display::mg = mg;
	stringstream title;
	title << "Projekt PEA";
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(title.str().c_str());

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutIdleFunc(animation);

	//glutKeyboardFunc(keyboard);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

#endif