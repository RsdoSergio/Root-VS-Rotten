#include "menu.h"
#include "freeglut.h"

extern float G_XMAX;
extern float G_YMAX;

struct OpcionMenu {
	const char* texto;
	float x;
	float y;
};

static void dibujaPrincipal(int opcion)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_menu_inicio.png").id);
	// Forzar máxima calidad
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2f(-G_XMAX, -G_YMAX);
	glTexCoord2d(1, 1); glVertex2f(G_XMAX, -G_YMAX);
	glTexCoord2d(1, 0); glVertex2f(G_XMAX, G_YMAX);
	glTexCoord2d(0, 0); glVertex2f(-G_XMAX, G_YMAX);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::setFont("fuentes/titulo.ttf", 85);
	ETSIDI::printxy("Root VS Rotten", -21.5f, 8.0f);

	OpcionMenu opciones[] = {
		{ "JUGAR",         -4.5f,  1.5f },
		{ "INSTRUCCIONES", -9.5f, -2.5f },
		{ "CREDITOS",      -6.0f, -5.5f },
		{ "SALIR",         -4.0f, -8.0f }
	};
	int numOpciones = 4;

	for (int i = 0; i < numOpciones; i++) {
		if (i == opcion) {
			ETSIDI::setTextColor(1.0f, 1.0f, 1.0f);
			ETSIDI::setFont("fuentes/texto.ttf", 48);
		}
		else {
			ETSIDI::setTextColor(0.55f, 0.55f, 0.55f);
			ETSIDI::setFont("fuentes/texto.ttf", 44);
		}
		ETSIDI::printxy(opciones[i].texto, opciones[i].x, opciones[i].y);
	}

	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("W/S o flechas para navegar                            ENTER para confirmar", -22.0f, -13.5f);

	glColor3ub(255, 255, 255);
	glDisable(GL_BLEND);
}

static void dibujaInstrucciones()
{
	// Fondo negro
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2f(-G_XMAX, -G_YMAX);
	glTexCoord2d(1, 1); glVertex2f(G_XMAX, -G_YMAX);
	glTexCoord2d(1, 0); glVertex2f(G_XMAX, G_YMAX);
	glTexCoord2d(0, 0); glVertex2f(-G_XMAX, G_YMAX);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 64);
	ETSIDI::printxy("INSTRUCCIONES", -11.0f, 10.5f);

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
	glTexCoord2d(0, 1); glVertex2f(-G_XMAX, -G_YMAX);
	glTexCoord2d(1, 1); glVertex2f(G_XMAX, -G_YMAX);
	glTexCoord2d(1, 0); glVertex2f(G_XMAX, G_YMAX);
	glTexCoord2d(0, 0); glVertex2f(-G_XMAX, G_YMAX);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 64);
	ETSIDI::printxy("CREDITOS", -8.5f, 10.5f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 35);
	ETSIDI::printxy("Desarrollo:", -6.0f, 7.5f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::setFont("fuentes/texto.ttf", 24);
	ETSIDI::printxy("Emmanuel Molina", -6.0f, 5.5f);
	ETSIDI::printxy("Mauricio Quinchuela", -8.0f, 2.5f);
	ETSIDI::printxy("Pablo Paz", -4.0f, -1.5f);
	ETSIDI::printxy("Tomas Estevez", -5.0f, -4.5f);
	ETSIDI::printxy("Sergio Rosado", -5.0f, -7.5f);

	ETSIDI::setTextColor(0.4f, 0.6f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 22);
	ETSIDI::printxy("ETSIDI - UPM  |  Informatica Industrial", -12.0f, -10.5f);

	// Volver
	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver al menu", -6.0f, -14.5f);

	glColor3ub(255, 255, 255);
}

void Menu::dibuja()
{
	if (pantalla == 0) dibujaPrincipal(opcion);
	if (pantalla == 1) dibujaInstrucciones();
	if (pantalla == 2) dibujaCreditos();
}

void Menu::dibujaTeclaMenu() const
{
	ETSIDI::setFont("fuentes/texto.ttf", 18);
	ETSIDI::setTextColor(0.3f, 0.3f, 0.3f);
	ETSIDI::printxy("M (Menu)", -25.f, -13.f);
}

void Menu::dibujaPausa(int opcion) const
{
	glEnable(GL_BLEND); 	// Activar transparencia para respetar el canal alfa del PNG (me lo ha dicho la IA)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_pausa.png").id);
	// Forzar máxima calidad
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2f(-G_XMAX, -G_YMAX);
	glTexCoord2d(1, 1); glVertex2f(G_XMAX, -G_YMAX);
	glTexCoord2d(1, 0); glVertex2f(G_XMAX, G_YMAX);
	glTexCoord2d(0, 0); glVertex2f(-G_XMAX, G_YMAX);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	ETSIDI::setFont("fuentes/texto.ttf", 75);
	ETSIDI::setTextColor(1.f, 1.f, 1.f);
	ETSIDI::printxy("PAUSA", -7.0f, 4.0f);

	OpcionMenu opciones[] = {
		{ "CONTINUAR", -7.6f, -3.0f },
		{ "SALIR",     -4.2f, -6.5f }
	};
	int numOpciones = 2;

	for (int i = 0; i < numOpciones; i++) {
		if (i == opcion) {
			ETSIDI::setTextColor(0.85f, 0.85f, 0.f);
			ETSIDI::setFont("fuentes/texto.ttf", 48);
		}
		else {
			ETSIDI::setTextColor(1.f, 1.f, 1.f);
			ETSIDI::setFont("fuentes/texto.ttf", 44);
		}
		ETSIDI::printxy(opciones[i].texto, opciones[i].x, opciones[i].y);
	}
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