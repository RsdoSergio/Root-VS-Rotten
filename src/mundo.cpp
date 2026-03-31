#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero/tablero.h"

void Mundo::inicializa() {
	inicializaTablero(tablero);
};
//Metodo se gestiona la pulsacion de teclas, y como afecta a la simulacion
void Mundo::tecla(unsigned char key)
{
	// de momento vacía
}

void Mundo::mueve()
{
	// de momento vacía
}

//Metodo que gestiona el dibujo de la simulacion
void Mundo::dibuja()
{
	//aqui es donde hay que poner el codigo de dibujo (2D sobre el plano XY)

	dibujaTablero(tablero);
}