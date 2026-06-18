#pragma once
#include "freeglut.h"
#include "vector2d.h"

class Obstaculo
{
	Vector2D pos;
	bool activo = false;
	double ancho = 3.0;
	double alto = 2.0;

public:
	Obstaculo() = default;

	void colocar(double x, double y, double w, double h)
	{
		pos.setValores(x, y);
		ancho = w;
		alto = h;
		activo = true;
	}

	void desactivar() { activo = false; }

	double getPosX() const { return pos.getX(); }
	double getPosY() const { return pos.getY(); }
	double getAncho() const { return ancho; }
	double getAlto() const { return alto; }
	double getXmin() const { return pos.getX() - ancho / 2.0; }
	double getXmax() const { return pos.getX() + ancho / 2.0; }
	double getYmin() const { return pos.getY() - alto / 2.0; }
	double getYmax()  const { return pos.getY() + alto / 2.0; }
	bool   estaActivo() const { return activo; }

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