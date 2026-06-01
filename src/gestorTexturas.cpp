#include "gestorTexturas.h"
#include "ETSIDI.h"
#include "freeglut.h"

void precargarTexturas() {
	glClear(GL_COLOR_BUFFER_BIT);
	ETSIDI::setFont("fuentes/texto.ttf", 40);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("Cargando...", -0.5f, 0.0f);
	glutSwapBuffers();

	ETSIDI::getTexture("imagenes/fondo_menu_inicio.png");
	ETSIDI::getTexture("imagenes/fondo_pausa.png");
	ETSIDI::getTexture("imagenes/fondo_archon.png");

	ETSIDI::getTexture("imagenes/fondo_arena1.png");
	ETSIDI::getTexture("imagenes/fondo_arena2.png");
	ETSIDI::getTexture("imagenes/fondo_arena3.png");
	ETSIDI::getTexture("imagenes/fondo_arena4.png");
	ETSIDI::getTexture("imagenes/fondo_arena5.png");
	ETSIDI::getTexture("imagenes/fondo_arena6.png");
	ETSIDI::getTexture("imagenes/fondo_arena7.png");
	ETSIDI::getTexture("imagenes/fondo_arena8.png");
	ETSIDI::getTexture("imagenes/fondo_arena9.png");
}