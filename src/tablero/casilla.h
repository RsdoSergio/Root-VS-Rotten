#pragma once

class Casilla {
public:
	enum TipoCasilla {
		NORMAL,
		PODER
	};

	TipoCasilla tipo;
	bool ocupada;
	unsigned char r, g, b; // Color de la casilla
	int fila, col;  // Posición en el tablero

	void inicializa(int f, int c, TipoCasilla t, unsigned char cr, unsigned char cg, unsigned char cb);
};