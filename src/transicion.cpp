#include "transicion.h"
#include "transicion.h"
#include "freeglut.h"

constexpr float DURACION_BARRIDO = 0.4f;
constexpr float VELOCIDAD = 1.0f / DURACION_BARRIDO;

void Transicion::cubrir()
{
	activa = true;
	cubierta = false;
	cubriendo = true;
	progreso = 0.0f;
}

void Transicion::descubrir()
{
	activa = true;
	cubierta = false;
	cubriendo = false;
	progreso = 0.0f;
}

void Transicion::actualiza(double dt)
{
	if (!activa) return;

	progreso += (float)dt * VELOCIDAD;

	if (progreso >= 1.0f)
	{
		progreso = 1.0f;
		if (cubriendo)
			cubierta = true;
		else
			activa = false;
	}
}

void Transicion::dibuja() const
{
	if (!activa) return;

	extern float G_XMAX;
	extern float G_YMAX;

	float ancho = 2.0f * G_XMAX;
	float edgeIzq;

	if (cubriendo)
		edgeIzq = G_XMAX - progreso * ancho;
	else
		edgeIzq = -G_XMAX - progreso * ancho;

	float edgeDer = edgeIzq + ancho;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(edgeIzq, -G_YMAX, 0);
	glVertex3f(edgeDer, -G_YMAX, 0);
	glVertex3f(edgeDer, G_YMAX, 0);
	glVertex3f(edgeIzq, G_YMAX, 0);
	glEnd();
	glColor3ub(255, 255, 255);
}