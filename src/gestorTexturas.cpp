#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"

void precargarTexturas() {
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/texto.ttf", 40);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("Cargando...  0%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_menu_inicio.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando...  9%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_pausa.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 18%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena1.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 27%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena2.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 36%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena3.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 45%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena4.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 54%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena5.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 63%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena6.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 72%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena7.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 81%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena8.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 90%", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_arena9.png");
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::printxy("Cargando... 100%", -0.5f, 0.0f);
	glutSwapBuffers();
}