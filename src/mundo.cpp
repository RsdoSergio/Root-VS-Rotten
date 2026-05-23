#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero/tablero.h"
#include "audio.h"
#include "audio.h"

void Mundo::inicializa() {
	tablero.inicializaTablero();
	Audio::playMusica("audio/INTRO.mp3", true);
};

//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	if (key == 'm') Audio::stopMusica();
}

void Mundo::mueve()
{
	// de momento vacía
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	//aqui es donde hay que poner el codigo de dibujo (2D sobre el plano XY)

	tablero.dibujaTablero();
}