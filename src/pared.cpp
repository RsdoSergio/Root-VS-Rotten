#include "pared.h"
#include "freeglut.h"

Pared::Pared(Vector2D l1, Vector2D l2) : limite1_(l1), limite2_(l2) {}

void Pared::dibuja() const
{
	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINES);
	glVertex2d(limite1_.getX(), limite1_.getY());
	glVertex2d(limite2_.getX(), limite2_.getY());
	glEnd();
	glEnable(GL_LIGHTING);
}