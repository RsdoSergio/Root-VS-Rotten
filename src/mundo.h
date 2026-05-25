#pragma once
#include<vector>
#include<iostream>
#include "tablero.h"
#include "pos.h"

class Mundo
{
	Tablero tablero;
	int turno = 0;

	Pos seleccionada;                    // Sustituye al pair<int,int>, mucho más legible
	std::vector<Pos> casillasValidas;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};