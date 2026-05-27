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

	//Pulsar "c" para probar la arena de combate
	if (key == 'c') { arena.estaActiva() ? arena.desactiva() : arena.activa(); }
	if (key == 'w' || key == 'W')  if (seleccionada.fila < FILAS - 1) seleccionada.fila++;
	if (key == 's' || key == 'S')  if (seleccionada.fila > 0)  seleccionada.fila--;
	if (key == 'a' || key == 'A')  if (seleccionada.col > 0)  seleccionada.col--;
	if (key == 'd' || key == 'D')  if (seleccionada.col < COLS - 1)  seleccionada.col++;

	cursor.mover(key);   // el cursor gestiona su propio movimiento
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
	else
	{
		//instrucciones para resetear el dibujo (sino da fallos al imprimir el tablero, piezas...)
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_DEPTH_TEST);
		glColor3ub(255, 255, 255);

		tablero.dibujaTablero();
		tablero.dibujaPiezas();
		arena.dibuja();
		cursor.dibuja();
	}
}