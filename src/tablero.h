#pragma once
#include "casilla.h"
#include"pos.h"
#include<vector>

class Cursor;

constexpr int FILAS = 9;
constexpr int COLS = 9;
constexpr float TAM_CELDA = 2.8f;

class Tablero {
public:
	void inicializaTablero();

	void colocarPiezasIniciales();

	 //recibe un cursor para poder dibujar el cursor. las casillas se siguen dibujando de igual manera
	
	Pieza* getPieza(Pos p) const;
	bool   estaOcupada(Pos p) const;

	void gestionarEntrada(Pos cursor, int& turno);
	void cancelarSeleccion();
	void dibuja(const Cursor& cursor);

private:

	void dibujaTablero(const Cursor& cursor);
	void dibujaPiezas();
	void marcaCasillasValidas();

	Casilla casillas[FILAS][COLS];
	Pos piezaSeleccionada;
	std::vector<Pos> casillasValidas;
	bool movimientoPendiente = false;

	std::vector<Pos> movimientosValidos(Pos origen);
	bool moverPieza(Pos origen, Pos destino);
};