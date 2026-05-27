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
	if (key == 'm') Audio::stopMusica();

	//Pulsar "c" para probar la arena de combate
	cursor.mover(key);

	if (key == 13) tablero.gestionarEntrada(cursor.getPosicion(), turno);
	if (key == 27) tablero.cancelarSeleccion();
}

void Mundo::mueve()
{
	// de momento vacía
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	//aqui es donde hay que poner el codigo de dibujo (2D sobre el plano XY)
	tablero.dibujaTablero(cursor);
	tablero.dibujaPiezas();
	arena.dibuja();
	tablero.marcaCasillasValidas();
	//cursor.dibuja();
}