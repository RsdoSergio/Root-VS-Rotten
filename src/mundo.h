#pragma once
#include <vector>
#include <iostream>
#include "tablero.h"
#include "cursor.h"
#include "pos.h"
#include "arena.h"
#include "pieza.h"
#include "peon.h"

class Mundo
{
	Tablero tablero;
	Cursor  cursor;                  // gestiona posicion y dibujo del cursor
	int     turno = 0;
	std::vector<Pos> casillasValidas;
	arena arena;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};
