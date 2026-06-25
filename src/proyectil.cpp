#include "proyectil.h"
#include "freeglut.h"
#include <ETSIDI.h>

Vector2D Proyectil::getPosProyectil() const
{
	return posicion; // ← faltaba esto
}

Vector2D Proyectil::getVelProyectil() const
{
	return velocidad; // ← faltaba esto
}

double Proyectil::getDamageProyectil() const
{
	return damage; // ← faltaba esto
}

bool Proyectil::getEstado() const
{
	return activo; // ← faltaba esto
}

void Proyectil::mueve(double dt)
{
	if (!activo) return;
	//todavia no hay aceleracion
	//se implmentara a posterior.
	posicion = posicion + velocidad * dt;

	if (duracion > 0.0)
	{
		tiempoVivo += dt;
		if (tiempoVivo >= duracion)
			desactivar();
	}
}

void Proyectil::dibuja() const
{
	if (!activo) return;
	if (invisible) return;
	glPushMatrix();
	glTranslated(posicion.getX(), posicion.getY(), 0);

	if (!rutaSprite.empty())
	{
		auto tex = ETSIDI::getTexture(rutaSprite.c_str());
		if (tex.id != 0)
		{
			float tam = 0.8f;
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, tex.id);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-tam, -tam);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(tam, -tam);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(tam, tam);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-tam, tam);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glColor3ub(255, 140, 0);
			glutSolidSphere(0.4, 12, 12);
		}
	}
	else
	{
		glColor3ub(255, 140, 0);
		glutSolidSphere(0.4, 12, 12);
	}

	glPopMatrix();
}