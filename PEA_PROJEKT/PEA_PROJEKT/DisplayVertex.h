#pragma once
#include "stdafx.h"
#include "DisplayEdge.h"

#include <gl/gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>

class DisplayVertex
{
public:
	DisplayVertex(uint number = 0);
	~DisplayVertex();

	uint number;
	double x, y;
	vector<DisplayEdge*> edges;

	void draw();
	
};

