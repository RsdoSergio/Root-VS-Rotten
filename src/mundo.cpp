#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero/tablero.h"

void Mundo::inicializa() {
	x_ojo = 0;
	y_ojo = 10;
	z_ojo = 20;
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
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, 0, 0.0,				// hacia que punto mira  (0,0,0)
		0.0, 1.0, 0.0);				// definimos hacia arriba (eje Y)

	//aqui es donde hay que poner el codigo de dibujo

	dibujaTablero(tablero);
}