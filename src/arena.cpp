#include "arena.h"
#include "freeglut.h"

void arena::dibujaFondo() const
{
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, SEMIALTO);
	glVertex2f(-SEMIANCHO, SEMIALTO);
	glEnd();
}

void arena::dibujaInterior() const
{
	glColor3ub(255, 0, 120);
	glBegin(GL_QUADS);
	glVertex2f(-SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, SEMIALTO);
	glVertex2f(-SEMIANCHO, SEMIALTO);
	glEnd();
}

void arena::dibujaMarco() const
{
	glLineWidth(5);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, -SEMIALTO);
	glVertex2f(SEMIANCHO, SEMIALTO);
	glVertex2f(-SEMIANCHO, SEMIALTO);
	glEnd();
}

void arena::dibuja() const
{
	if (!activo) return;
	dibujaFondo();
	dibujaInterior();
	dibujaMarco();
}
