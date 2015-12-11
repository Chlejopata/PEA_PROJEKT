#pragma once
#include "stdafx.h"

#include <gl/gl.h>
#include <gl/GLU.h>
#include <gl/glut.h>

class DisplayVertex;

class DisplayEdge
{
public:
	DisplayEdge();
	~DisplayEdge();
	int weight;

	DisplayVertex *start, *end;

	void draw();
};

