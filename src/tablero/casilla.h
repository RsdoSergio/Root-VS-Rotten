#pragma once

class Casilla {
public:
	enum TipoCasilla {
		NORMAL,
		PODER
	};

	TipoCasilla tipo;
	bool ocupada;
	using byte = unsigned char;
	byte r, g, b; // Color de la casilla
	int fila, col;  // Posición en el tablero

	void inicializa(int f, int c, TipoCasilla t, byte cr, byte cg, byte cb);
};