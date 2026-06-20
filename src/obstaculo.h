#pragma once
#include "freeglut.h"
#include "vector2d.h"
#include "ETSIDI.h"
#include <string>

class Obstaculo
{
	Vector2D pos;
	bool activo = false;
	double ancho = 3.0;
	double alto = 2.0;
	std::string sprite = "imagenes/obstaculos/obs1.png"; //valor x defecto

public:
	Obstaculo() = default;

	void colocar(double x, double y, double w, double h, const std::string& spr = "imagenes/obstaculos/obs1.png")
	{
		pos.setValores(x, y);
		ancho = w;
		alto = h;
		sprite = spr;
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

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(sprite.c_str()).id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2d(getXmin(), getYmin());
		glTexCoord2d(1, 1); glVertex2d(getXmax(), getYmin());
		glTexCoord2d(1, 0); glVertex2d(getXmax(), getYmax());
		glTexCoord2d(0, 0); glVertex2d(getXmin(), getYmax());
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
};