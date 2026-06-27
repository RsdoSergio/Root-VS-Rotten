#include "menu.h"
#include "freeglut.h"
#include "audio.h"
#include "puntuaciones.h"

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
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondos/fondo_menu_inicio.png").id);
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
		{ "JUGAR",         -4.5f,  3.0f },
		{ "CONTROLES",	   -7.0f,  0.0f },
		{ "CREDITOS",      -6.0f, -3.0f },
		{ "PUNTUACIONES",  -9.0f, -6.0f },
		{ "SALIR",         -4.0f, -9.0f }
	};

	int numOpciones = 5;

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
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2f(-G_XMAX, -G_YMAX);
	glTexCoord2d(1, 1); glVertex2f(G_XMAX, -G_YMAX);
	glTexCoord2d(1, 0); glVertex2f(G_XMAX, G_YMAX);
	glTexCoord2d(0, 0); glVertex2f(-G_XMAX, G_YMAX);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/titulo.ttf", 64);
	ETSIDI::printxy("CONTROLES", -10.0f, 11.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("TABLERO", -18.0f, 7.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("W / A / S / D", -18.0f, 5.0f);
	ETSIDI::printxy("Flechas", -18.0f, 4.0f);
	ETSIDI::printxy("ENTER", -18.0f, 3.0f);
	ETSIDI::printxy("ESC", -18.0f, 2.0f);
	ETSIDI::printxy("M", -18.0f, 1.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Mover cursor Planta", -5.0f, 5.0f);
	ETSIDI::printxy("Mover cursor Zombi", -5.0f, 4.0f);
	ETSIDI::printxy("Seleccionar pieza / casilla", -5.0f, 3.0f);
	ETSIDI::printxy("Cancelar seleccion", -5.0f, 2.0f);
	ETSIDI::printxy("Pausa", -5.0f, 1.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("HECHIZOS", -18.0f, -1.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("ESPACIO", -18.0f, -3.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Ver hechizos del Mago (con el Mago seleccionado)", -5.0f, -3.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("ARENA (COMBATE)", -18.0f, -5.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("W / A / S / D", -18.0f, -7.0f);
	ETSIDI::printxy("Flechas", -18.0f, -8.0f);
	ETSIDI::printxy("Q", -18.0f, -9.0f);
	ETSIDI::printxy("K", -18.0f, -10.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Mover pieza Planta", -5.0f, -7.0f);
	ETSIDI::printxy("Mover pieza Zombi", -5.0f, -8.0f);
	ETSIDI::printxy("Atacar (Planta)", -5.0f, -9.0f);
	ETSIDI::printxy("Atacar (Zombi)", -5.0f, -10.0f);

	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver al menu", -6.0f, -14.5f);
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

	ETSIDI::setTextColor(1.0f, 0.1f, 0.2f);
	ETSIDI::setFont("fuentes/titulo.ttf", 64);
	ETSIDI::printxy("CREDITOS", -10.5f, 10.5f);

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
	if (pantalla == 3) dibujaPuntuaciones();
}

void Menu::dibujaPausa(int opcion) const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondos/fondo_pausa.png").id);
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
		{ "CONTINUAR", -7.6f, -1.5f },
		{ "CONTROLES", -7.6f, -4.5f },
		{ "SALIR",     -4.2f, -7.5f }
	};
	int numOpciones = 3;

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
		if (key == 'w' || key == 'W') {
			opcion = (opcion - 1 + 5) % 5;   //sube, con vuelta al final
			Audio::playSonido("audio/MENU.mp3");
		}
		if (key == 's' || key == 'S')
			opcion = (opcion + 1) % 5;        //baja, con vuelta al principio
		Audio::playSonido("audio/MENU.mp3");
	}
	if (key == 13)
	{
		Audio::playSonido("audio/SELECCION_EN_MENU.mp3");
		if (opcion == 0) confirmadoJugar = true;
		if (opcion == 1) pantalla = 1;
		if (opcion == 2) pantalla = 2;
		if (opcion == 3) pantalla = 3;
		if (opcion == 4) exit(0);
	}

	//Pantallas secundarias
	if (pantalla == 1 || pantalla == 2 || pantalla == 3)
	{
		if (key == 27)  // ESC
			pantalla = 0;
	}
}

void Menu::dibujaControlesPausa() const
{
	extern float G_XMAX;
	extern float G_YMAX;

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-G_XMAX, -G_YMAX);
	glVertex2f(G_XMAX, -G_YMAX);
	glVertex2f(G_XMAX, G_YMAX);
	glVertex2f(-G_XMAX, G_YMAX);
	glEnd();

	ETSIDI::setTextColor(0.2f, 1.0f, 0.2f);
	ETSIDI::setFont("fuentes/titulo.ttf", 64);
	ETSIDI::printxy("CONTROLES", -10.0f, 11.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("TABLERO", -18.0f, 7.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("W / A / S / D", -18.0f, 5.0f);
	ETSIDI::printxy("Flechas", -18.0f, 4.0f);
	ETSIDI::printxy("ENTER", -18.0f, 3.0f);
	ETSIDI::printxy("ESC", -18.0f, 2.0f);
	ETSIDI::printxy("M", -18.0f, 1.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Mover cursor Planta", -5.0f, 5.0f);
	ETSIDI::printxy("Mover cursor Zombi", -5.0f, 4.0f);
	ETSIDI::printxy("Seleccionar pieza / casilla", -5.0f, 3.0f);
	ETSIDI::printxy("Cancelar seleccion", -5.0f, 2.0f);
	ETSIDI::printxy("Pausa", -5.0f, 1.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("HECHIZOS", -18.0f, -1.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("ESPACIO", -18.0f, -3.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Ver hechizos del Mago (con el Mago seleccionado)", -5.0f, -3.0f);

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/texto.ttf", 26);
	ETSIDI::printxy("ARENA (COMBATE)", -18.0f, -5.0f);

	ETSIDI::setTextColor(0.5f, 0.85f, 1.0f);
	ETSIDI::setFont("fuentes/texto.ttf", 21);
	ETSIDI::printxy("W / A / S / D", -18.0f, -7.0f);
	ETSIDI::printxy("Flechas", -18.0f, -8.0f);
	ETSIDI::printxy("Q", -18.0f, -9.0f);
	ETSIDI::printxy("K", -18.0f, -10.0f);

	ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);
	ETSIDI::printxy("Mover pieza Planta", -5.0f, -7.0f);
	ETSIDI::printxy("Mover pieza Zombi", -5.0f, -8.0f);
	ETSIDI::printxy("Atacar (Planta)", -5.0f, -9.0f);
	ETSIDI::printxy("Atacar (Zombi)", -5.0f, -10.0f);

	ETSIDI::setTextColor(0.4f, 0.4f, 0.4f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver a la pausa", -6.0f, -14.5f);
	glColor3ub(255, 255, 255);
}

void Menu::dibujaPuntuaciones() const
{
	extern float G_XMAX;
	extern float G_YMAX;

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-G_XMAX, -G_YMAX);
	glVertex2f(G_XMAX, -G_YMAX);
	glVertex2f(G_XMAX, G_YMAX);
	glVertex2f(-G_XMAX, G_YMAX);
	glEnd();

	ETSIDI::setTextColor(1.0f, 0.85f, 0.2f);
	ETSIDI::setFont("fuentes/titulo.ttf", 64);
	ETSIDI::printxy("MEJORES TIEMPOS", -19.0f, 10.0f);

	auto lista = Puntuaciones::cargar();

	if (lista.empty())
	{
		ETSIDI::setTextColor(0.6f, 0.6f, 0.6f);
		ETSIDI::setFont("fuentes/texto.ttf", 35);
		ETSIDI::printxy("NO HAY PUNTUACIONES REGISTRADAS", -18.f, -0.f);
	}
	else
	{
		float y = 6.0f;
		for (int i = 0; i < (int)lista.size(); i++)
		{
			//puesto
			if (i == 0) ETSIDI::setTextColor(1.0f, 0.85f, 0.0f);
			else if (i == 1) ETSIDI::setTextColor(0.75f, 0.75f, 0.75f);
			else if (i == 2) ETSIDI::setTextColor(0.7f, 0.4f, 0.1f);
			else ETSIDI::setTextColor(0.85f, 0.85f, 0.85f);

			ETSIDI::setFont("fuentes/auxiliar.ttf", 32);

			std::string puesto = std::to_string(i + 1) + ".";
			ETSIDI::printxy(puesto.c_str(), -8.0f, y);

			std::string tiempo = Puntuaciones::formatearTiempo(lista[i].segundos);
			ETSIDI::printxy(tiempo.c_str(), -4.0f, y);

			ETSIDI::printxy(lista[i].nombre.c_str(), 2.0f, y);

			y -= 2.0f;
		}
	}

	ETSIDI::setTextColor(0.5f, 0.5f, 0.5f);
	ETSIDI::setFont("fuentes/texto.ttf", 20);
	ETSIDI::printxy("ESC - Volver al menu", -7.0f, -14.5f);
	glColor3ub(255, 255, 255);
}