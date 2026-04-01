#pragma once
#include "tablero/tablero.h"
#include "combate/pared.h"
#include "combate/caja.h"

class Mundo
{
	Tablero tablero;
	caja cajaCombate;
public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};