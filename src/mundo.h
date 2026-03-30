#pragma once
#include "tablero/tablero.h"

class Mundo
{
	double x_ojo;
	double y_ojo;
	double z_ojo;
	Tablero tablero;
public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};