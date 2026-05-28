#pragma once
#include <vector>
#include <iostream>
#include "tablero.h"
#include "cursor.h"
#include "pos.h"
#include "arena.h"
#include "listapieza.h"

class Mundo
{
	Tablero tablero;
	Pos seleccionada;                    
	Pos piezaSeleccionada;
	Cursor  cursor; // gestiona posicion y dibujo del cursor
	listapieza ListaPieza;
	int     turno = 0;
	std::vector<Pos> casillasValidas;
	arena arena;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};
