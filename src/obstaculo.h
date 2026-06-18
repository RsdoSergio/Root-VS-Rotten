#pragma once
#include "freeglut.h"
#include "vector2d.h"

constexpr double OBS_ANCHO = 4.0;
constexpr double OBS_ALTO = 2.0;

class Obstaculo
{
	Vector2D pos;
	bool activo = false;

public:
	Obstaculo() = default;

	void colocar(double x, double y)
	{
		pos.setValores(x, y);
		activo = true;
	}

	double getXmin() const { return pos.getX() - OBS_ANCHO / 2.0; }
	double getXmax() const { return pos.getX() + OBS_ANCHO / 2.0; }
	double getYmin() const { return pos.getY() - OBS_ALTO / 2.0; }
	double getYmax() const { return pos.getY() + OBS_ALTO / 2.0; }

	void dibuja() const
	{
		if (!activo) return;
		glDisable(GL_LIGHTING);

		glColor3ub(80, 80, 80);
		glBegin(GL_QUADS);
		glVertex2d(getXmin(), getYmin());
		glVertex2d(getXmax(), getYmin());
		glVertex2d(getXmax(), getYmax());
		glVertex2d(getXmin(), getYmax());
		glEnd();

		glColor3ub(220, 220, 220);
		glLineWidth(2.0f);
		glBegin(GL_LINE_LOOP);
		glVertex2d(getXmin(), getYmin());
		glVertex2d(getXmax(), getYmin());
		glVertex2d(getXmax(), getYmax());
		glVertex2d(getXmin(), getYmax());
		glEnd();
		glLineWidth(1.0f);
	}
};