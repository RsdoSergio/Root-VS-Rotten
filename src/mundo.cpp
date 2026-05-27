#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero.h"
#include <vector>
#include "audio.h"
#include "audio.h"

void Mundo::inicializa() {
	tablero.inicializaTablero();
	tablero.colocarPiezasIniciales();

	//inicializacion de piezas para el juego

	//inicializacion de peones para ambos bandos
	const float TAM = 2.8f; //tener presente el tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;
	Audio::playMusica("audio/INTRO.mp3", true);
};

//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	if (!enPartida)
	{
		menu.tecla(key);
		if (menu.seEligeJugar())
			enPartida = true;
		return;   // el tablero y el cursor no tocan nada
	}

	if (key == 'm') Audio::stopMusica();

	cursor.mover(key);
	if (key == 13) {
		bool combate = tablero.gestionarEntrada(cursor.getPosicion(), turno);
		if (combate) {
			arena.fDatos(*tablero.getPersonaje1(), *tablero.getPersonaje2());
			arena.activa();
		}
	}
	//Pulsar "c" para probar la arena de combate
	if (key == 'c') {
		Peon p1(Bando::planta, Pos(0, 0));
		Peon p2(Bando::zombi, Pos(1, 0));
		arena.fDatos(p1, p2);
		arena.activa();
	}
	if (key == 'v') arena.desactiva();
}

void Mundo::mueve()
{
	// de momento vacía
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	if (!enPartida)
	{
		menu.dibuja();
		return;
	}

	//Resets necesarios sino no funciona bien
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glColor3ub(255, 255, 255);

	tablero.dibuja(cursor);
	arena.dibuja();
}