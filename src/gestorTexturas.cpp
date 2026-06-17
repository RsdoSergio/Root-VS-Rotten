#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"

void precargarTexturas() {
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/texto.ttf", 50);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("Cargando...  0%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_menu_inicio.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando...  9%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_pausa.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 18%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena1.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 27%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena2.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 36%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena3.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 45%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena4.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 54%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena5.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 63%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena6.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 72%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena7.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 81%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena8.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 90%", -10.0f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena9.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 100%", -10.0f, 0.0f);
	glutSwapBuffers();
}