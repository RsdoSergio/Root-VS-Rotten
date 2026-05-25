#include "pared.h"
#include <freeglut.h>

void pared::dibuja()
{
	glDisable(GL_LIGHTING);
	glColor3ub(colorPared.r, colorPared.g, colorPared.b);
	glBegin(GL_LINES);
	glVertex3d(limite1.x, limite1.y, 0);
	glVertex3d(limite2.x, limite2.y, 0);
	glVertex3d(limite2.x, limite2.y, 0);
	glVertex3d(limite1.x, limite1.y, 0);
	glEnd();
	glEnable(GL_LIGHTING);
}

