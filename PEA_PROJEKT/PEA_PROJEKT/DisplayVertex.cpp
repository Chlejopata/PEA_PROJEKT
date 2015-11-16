#include "DisplayVertex.h"


DisplayVertex::DisplayVertex(uint number)
{
	this->number = number;
	x = y = number;
}


DisplayVertex::~DisplayVertex()
{
}

void DisplayVertex::draw()
{
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 5.0, y - 5.0);
	glVertex2d(x - 5.0, y + 5.0);
	glVertex2d(x + 5.0, y + 5.0);
	glVertex2d(x + 5.0, y - 5.0);
	glEnd();
}