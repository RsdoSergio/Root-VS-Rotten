#pragma once
#include<vector>
#include<iostream>
#include "tablero.h"
#include "pos.h"
#include "tablero/tablero.h"
#include "combate/pared.h"
#include "combate/caja.h"

class Mundo
{
	Tablero tablero;
	int turno = 0;

	Pos seleccionada;                    // Sustituye al pair<int,int>, mucho más legible
	std::vector<Pos> casillasValidas;

	caja cajaCombate;
public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};