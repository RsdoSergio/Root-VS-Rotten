#pragma once
#include "casilla.h"

// Dimensiones del tablero
constexpr int FILAS = 9;
constexpr  int COLS = 9;
constexpr float TAM_CELDA = 2.8f;

class Tablero {
public:
	void inicializaTablero();
	void dibujaTablero();

private:
	Casilla casillas[FILAS][COLS];
};
