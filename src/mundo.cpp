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
	{	//tengo problemas para establercer la pos inicial de las piezas
		
		//Peon.setTipo(peon);//añadir etiquita peon
		//Peon.setVida(12);
		//Peon.setFuerza(4);
		//Peon.setVelpieza(5.0, 5.0);
		//no tiene proyectil

		Planta.push_back(Pieza(peon,12.0,4.0,0,0));
		Zombi.push_back(Pieza(peon, 12.0, 4.0, 0, 0));
	}

	//inicializacion de golems, valquiria, unicornio

	for (int i = 0; i < 2; i++)
	{
		/*/Pieza Golem, Valquiria, Unicornio;
		Golem.setTipo(golem);
		Golem.setVida(24);
		Golem.setFuerza(10);
		Golem.setVelpieza(3.0, 3.0);
		Planta.push_back(Golem);
		Zombi.push_back(Golem);

		Valquiria.setTipo(valquiria);
		Valquiria.setVida(10);
		Valquiria.setFuerza(2);
		Valquiria.setVelpieza(6.5, 6.5);
		Planta.push_back(Valquiria);
		Zombi.push_back(Valquiria);

		*/
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