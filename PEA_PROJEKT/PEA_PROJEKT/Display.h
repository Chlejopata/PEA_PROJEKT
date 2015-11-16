#pragma once
#include "stdafx.h"
#include "MatrixGraph.h"
#include "DisplayVertex.h"
#include "DisplayEdge.h"

#include <gl/gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>

class Display
{
public:
	Display();
	~Display();
	static void initializeGraphics(MatrixGraph *mg);
private:
	static void renderScene(void);
	static void changeSize(GLsizei horizontal, GLsizei vertical);
	static MatrixGraph* mg;
	static GLdouble dimensions;
	static bool parsed;

	static vector<DisplayVertex> vertices;
	static vector<DisplayEdge> edges;
};

