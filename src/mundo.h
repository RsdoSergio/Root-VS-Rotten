#pragma once
#include <vector>
#include <iostream>
#include "tablero.h"
#include "cursor.h"
#include "pos.h"
#include "arena.h"
#include "pieza.h"
#include "peon.h"
#include "menu.h"

class Mundo
{
	Tablero tablero;
	
	Cursor cursor{ 4, 4, 255, 220,   0 };  // amarillo
	Cursor cursor2{ 4, 4, 180,   0, 255 };  //morado
	int     turno = 0;
	std::vector<Pos> casillasValidas;
	arena arena;
	Menu    menu;
	bool    enPartida = false;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
	void teclaEspecial(int key);   // flechas del teclado para cursor2
};
