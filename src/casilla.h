#pragma once

class Pieza;//avisar de que existe
using byte = unsigned char;

class Casilla
{
public:
	enum TipoCasilla {
		NORMAL,
		PODER
	};

	TipoCasilla tipo;
	bool ocupada;
	using byte = unsigned char;
	byte r, g, b;
	int fila, col;  // Posición en el tablero
	Pieza* pieza = nullptr; //Puntero a la pieza que ocupa la casilla

	bool CasOcupada() const { return pieza != nullptr; }
	bool CasPoder() const { return tipo == PODER; }

	void inicializa(int f, int c, TipoCasilla t, byte cr, byte cg, byte cb);

	void setColor(byte cr, byte cg, byte cb) { r = cr; g = cg; b = cb; }
};