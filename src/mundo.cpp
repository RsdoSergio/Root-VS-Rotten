#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero/tablero.h"
feature/Herencia_Piezas/Emmanuel
#include <vector>
#include "audio.h"
#include "audio.h"


void Mundo::inicializa() {
	tablero.inicializaTablero();

	//inicializacion de piezas para el juego
Audio::playMusica("audio/INTRO.mp3", true);
	//inicializacion de peones para ambos bandos
	const float TAM = 2.8f; //tener presente el tamaño de cada celda
	const float pos = (9 * TAM) / 2.0f;

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