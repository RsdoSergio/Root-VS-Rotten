#include "mundo.h"
#include "freeglut.h"
#include <cmath>
#include "tablero/tablero.h"
#include <vector>



void Mundo::inicializa() {
	tablero.inicializaTablero();

	//inicializacion de piezas para el juego

	//inicializacion de peones para ambos bandos

	for (int i = 0; i < 8; i++)
	{
		Pieza Peon;
		Peon.setTipo(peon);//añadir etiquita peon
		Peon.setVida(12);
		Peon.setFuerza(4);
		Peon.setVelpieza(5.0, 5.0);
		//no tiene proyectil

		Planta.push_back(Peon);
		Zombi.push_back(Peon);
	}


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

	tablero.dibujaTablero();
}