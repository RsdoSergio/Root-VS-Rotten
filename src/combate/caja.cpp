#include "caja.h"
#include "freeglut.h"
#include <string>

void caja::dibuja()
{
	suelo.dibuja();
	techo.dibuja();
	izquierda.dibuja();
	derecha.dibuja();

	dibujaHUD();
}

void caja::fDatos(const pieza& p1, const pieza& p2)
{

	vida1 = p1.getVida();
	vidamax1 = p1.getVidamax();
	nombre1 = p1.getNombre();
	vida2 = p2.getVida();
	vidamax2 = p2.getVidamax();
	nombre2 = p2.getNombre();

}

void caja::dibujaHUD()
{
	double prop1 = vida1 / vidamax1;
	double prop2 = vida2 / vidamax2;
	dibujaVida(-a_2, h_2 + 0.5, ancho / 2 - 0.5, h_HUD, prop1, 255, 0, 0);
	dibujaVida(0.5, h_2 + 0.5, ancho / 2 - 0.5, h_HUD, prop2, 0, 255, 0);
	dibujaNombre(nombre1, -a_2 + 0.5, h_2 + h_HUD + 0.5);
	dibujaNombre(nombre2, 0.5, h_2 + h_HUD + 0.5);
}

void caja::dibujaVida(double x, double y, double w, double h, double prop, int r, int g, int b)
{
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2d(x, y);
	glVertex2d(x + w * prop, y);
	glVertex2d(x + w * prop, y + h);
	glVertex2d(x, y + h);
	glEnd();

	if (prop > 0.0) {
		glColor3ub(r, g, b);
		glVertex2d(x, y);
		glVertex2d(x + w * prop, y);
		glVertex2d(x + w * prop, y + h);
		glVertex2d(x, y + h);
		glEnd();
	}
}

void caja::dibujaNombre(const std::string& nombre, double x, double y)
{
	glColor3ub(255, 255, 255);
	glRasterPos2d(x, y);
	for (char c : nombre) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}