#pragma once
#include "pos.h"
#include "tablero.h"

class Cursor
{
	Pos posicion;   // casilla donde se encuentra el cursor ahora mismo

public:
	Cursor();             
	void mover(unsigned char key);   // actualiza posicion
	void dibuja() const;             // dibuja el borde
	Pos  getPosicion() const { return posicion; }
};
