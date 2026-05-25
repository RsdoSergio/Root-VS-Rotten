#pragma once

class Pieza;//avisar de que existe

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
	byte r, g, b; // Color de la casilla
	int fila, col;  // Posición en el tablero
	Pieza* pieza = nullptr; //Puntero a la pieza que ocupa la casilla (vacía? = nullptr)

	bool CasOcupada() const { return pieza != nullptr; } //true si la casilla esta ocupada
	bool CasPoder() const { return tipo == PODER; }//true si es casilla especial

	void inicializa(int f, int c, TipoCasilla t, byte cr, byte cg, byte cb);
};