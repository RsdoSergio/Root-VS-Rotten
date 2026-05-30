#pragma once
#include "pos.h"
#include "tablero.h"

class Cursor
{
	Pos posicion;   // casilla donde se encuentra el cursor ahora mismo
	unsigned char cr, cg, cb;

public:
	friend class Tablero;

	// Constructor: posicion inicial + color del borde
	Cursor(int fila, int col, unsigned char r, unsigned char g, unsigned char b);

	void mover(unsigned char key);        // WASD 
	void moverFlechas(int key);          // flechas del teclado 
	void dibuja() const;
	Pos  getPosicion() const { return posicion; }
};
