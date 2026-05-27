#pragma once
#include<vector>
#include<iostream>
#include "tablero.h"
#include "pos.h"
#include "arena.h"
#include "pieza.h"
#include "peon.h"

class Mundo
{
	Tablero tablero;
	int turno = 0;

	Pos seleccionada;                    // Sustituye al pair<int,int>, mucho más legible
	std::vector<Pos> casillasValidas;

	arena arena;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};
