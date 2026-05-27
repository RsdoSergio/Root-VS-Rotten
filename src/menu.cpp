#include "menu.h"
#include "freeglut.h"

static void dibujaPrincipal(int opcion)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -15.0f);
	glVertex2f(25.0f, -15.0f);
	glVertex2f(25.0f, 15.0f);
	glVertex2f(-25.0f, 15.0f);
	glEnd();

	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::setFont("fuentes/titulo.ttf", 80);
	ETSIDI::printxy("Root VS Rotten", -20.0f, 8.0f);

	ETSIDI::setTextColor(0.8f, 0.8f, 0.8f);
	ETSIDI::setFont("fuentes/subtitulo.ttf", 28);
	ETSIDI::printxy("UN JUEGO DE ESTRATEGIA POR TURNOS", -11.0f, 5.5f);

	//JUGAR
	if (opcion == 0) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.6f, 0.1f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2f(-7.0f, 0.5f - 0.8f); glVertex2f(7.0f, 0.5f - 0.8f);
		glVertex2f(7.0f, 0.5f + 1.2f); glVertex2f(-7.0f, 0.5f + 1.2f);
		glEnd();
		glDisable(GL_BLEND);
		ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
		ETSIDI::setFont("fuentes/texto.ttf", 48);
		ETSIDI::printxy("> JUGAR <", -5.5f, 1.5f);
	}
	else {
		ETSIDI::setTextColor(0.55f, 0.55f, 0.55f);
		ETSIDI::setFont("fuentes/texto.ttf", 44);
		ETSIDI::printxy("JUGAR", -3.5f, 1.5f);
	}

	//INSTRUCCIONES
	if (opcion == 1) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.6f, 0.1f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2f(-10.0f, -2.5f - 0.8f); glVertex2f(10.0f, -2.5f - 0.8f);
		glVertex2f(10.0f, -2.5f + 1.2f); glVertex2f(-10.0f, -2.5f + 1.2f);
		glEnd();
		glDisable(GL_BLEND);
		ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
		ETSIDI::setFont("fuentes/texto.ttf", 48);
		ETSIDI::printxy("> INSTRUCCIONES <", -11.5f, -2.5f);
	}
	else {
		ETSIDI::setTextColor(0.55f, 0.55f, 0.55f);
		ETSIDI::setFont("fuentes/texto.ttf", 44);
		ETSIDI::printxy("INSTRUCCIONES", -9.0f, -2.5f);
	}

	//CREDITOS
	if (opcion == 2) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.6f, 0.1f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2f(-7.0f, -5.5f - 0.8f); glVertex2f(7.0f, -5.5f - 0.8f);
		glVertex2f(7.0f, -5.5f + 1.2f); glVertex2f(-7.0f, -5.5f + 1.2f);
		glEnd();
		glDisable(GL_BLEND);
		ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
		ETSIDI::setFont("fuentes/texto.ttf", 48);
		ETSIDI::printxy("> CREDITOS <", -7.5f, -5.5f);
	}
	else {
		ETSIDI::setTextColor(0.55f, 0.55f, 0.55f);
		ETSIDI::setFont("fuentes/texto.ttf", 44);
		ETSIDI::printxy("CREDITOS", -5.5f, -5.5f);
	}

	//SALIR
	if (opcion == 3) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.6f, 0.1f, 0.35f);
		glBegin(GL_QUADS);
		glVertex2f(-7.0f, -8.5f - 0.8f); glVertex2f(7.0f, -8.5f - 0.8f);
		glVertex2f(7.0f, -8.5f + 1.2f); glVertex2f(-7.0f, -8.5f + 1.2f);
		glEnd();
		glDisable(GL_BLEND);
		ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
		ETSIDI::setFont("fuentes/texto.ttf", 48);
		ETSIDI::printxy("> SALIR <", -5.5f, -8.f);
	}
	else {
		ETSIDI::setTextColor(0.55f, 0.55f, 0.55f);
		ETSIDI::setFont("fuentes/texto.ttf", 44);
		ETSIDI::printxy("SALIR", -3.5f, -8.f);
	}

	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("W/S o flechas para navegar   |   ENTER para confirmar", -13.0f, -13.5f);

	glColor3ub(255, 255, 255);
	glDisable(GL_BLEND);
}

static void dibujaInstrucciones()
{
	// Fondo negro
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -15.0f);
	glVertex2f(25.0f, -15.0f);
	glVertex2f(25.0f, 15.0f);
	glVertex2f(-25.0f, 15.0f);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 64);
	ETSIDI::printxy("INSTRUCCIONES", -11.0f, 10.5f);

	glColor3f(0.2f, 0.7f, 0.2f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(-18.0f, 9.0f);
	glVertex2f(18.0f, 9.0f);
	glEnd();
	glLineWidth(1.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("W / S", -18.0f, 7.0f);
	ETSIDI::printxy("A / D", -18.0f, 4.5f);
	ETSIDI::printxy("ENTER", -18.0f, 2.0f);
	ETSIDI::printxy("ESC", -18.0f, -0.5f);
	ETSIDI::printxy("C", -18.0f, -3.0f);
	ETSIDI::printxy("M", -18.0f, -5.5f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Mover cursor arriba / abajo", -10.0f, 7.0f);
	ETSIDI::printxy("Mover cursor izquierda / derecha", -10.0f, 4.5f);
	ETSIDI::printxy("Seleccionar pieza o casilla", -10.0f, 2.0f);
	ETSIDI::printxy("Cancelar seleccion", -10.0f, -0.5f);
	ETSIDI::printxy("Activar / desactivar arena", -10.0f, -3.0f);
	ETSIDI::printxy("Silenciar musica", -10.0f, -5.5f);

	glColor3f(0.2f, 0.7f, 0.2f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(-18.0f, -7.0f);
	glVertex2f(18.0f, -7.0f);
	glEnd();
	glLineWidth(1.0f);

	ETSIDI::setTextColor(0.6f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 22);
	ETSIDI::printxy("--------------------------------------------------", -18.0f, -8.5f);
	ETSIDI::printxy("--------------------------------------------------", -18.0f, -10.5f);
	ETSIDI::printxy("--------------------------------------------------", -18.0f, -12.5f);

	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver al menu", -5.0f, -14.5f);

	glColor3ub(255, 255, 255);
}

static void dibujaCreditos()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -15.0f);
	glVertex2f(25.0f, -15.0f);
	glVertex2f(25.0f, 15.0f);
	glVertex2f(-25.0f, 15.0f);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 64);
	ETSIDI::printxy("CREDITOS", -7.5f, 10.5f);

	glColor3f(0.2f, 0.7f, 0.2f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(-18.0f, 9.0f);
	glVertex2f(18.0f, 9.0f);
	glEnd();
	glLineWidth(1.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 30);
	ETSIDI::printxy("Desarrollo:", -18.0f, 7.5f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::setFont("fuentes/texto.ttf", 24);
	ETSIDI::printxy("Emmanuel Molina", -18.0f, 5.5f);
	ETSIDI::printxy("Mauricio Quinchuela", -18.0f, 3.5f);
	ETSIDI::printxy("Pablo Paz", -18.0f, 1.5f);
	ETSIDI::printxy("Tomás Estevez", -18.0f, -1.5f);
	ETSIDI::printxy("Sergio Rosado", -18.0f, -3.5f);

	glColor3f(0.2f, 0.7f, 0.2f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex2f(-18.0f, -8.5f);
	glVertex2f(18.0f, -8.5f);
	glEnd();
	glLineWidth(1.0f);

	ETSIDI::setTextColor(0.4f, 0.6f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 22);
	ETSIDI::printxy("ETSIDI - UPM  |  Informatica Industrial", -11.0f, -10.5f);

	// Volver
	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver al menu", -5.0f, -14.5f);

	glColor3ub(255, 255, 255);
}

void Menu::dibuja()
{
	if (pantalla == 0) dibujaPrincipal(opcion);
	if (pantalla == 1) dibujaInstrucciones();
	if (pantalla == 2) dibujaCreditos();
}

void Menu::tecla(unsigned char key)
{
	//Menu principal
	if (pantalla == 0)
	{
		if (key == 'w' || key == 'W')
			opcion = (opcion - 1 + 4) % 4;   //sube, con vuelta al final

		if (key == 's' || key == 'S')
			opcion = (opcion + 1) % 4;        //baja, con vuelta al principio

		if (key == 13)
		{
			if (opcion == 0) confirmadoJugar = true;
			if (opcion == 1) pantalla = 1;
			if (opcion == 2) pantalla = 2;
			if (opcion == 3) exit(0);
		}
	}

	//Pantallas secundarias
	if (pantalla == 1 || pantalla == 2)
	{
		if (key == 27)  // ESC
			pantalla = 0;
	}
}