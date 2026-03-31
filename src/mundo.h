#pragma once
#include "tablero/tablero.h"

class Mundo
{
	Tablero tablero;
public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};