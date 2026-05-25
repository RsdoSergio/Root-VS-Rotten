#pragma once
#include "casilla.h"
#include"pos.h"

constexpr int FILAS = 9;
constexpr int COLS = 9;
constexpr float TAM_CELDA = 2.8f;

class Tablero {
public:
    void inicializaTablero();
	void dibujaTablero(Pos cursor); //añadido argumento cursor para dibujar el borde del cursor en la casilla activa
    //← solo esta, sin duplicados ni vector/pair
    void colocarPiezasIniciales();

private:
    Casilla casillas[FILAS][COLS];
};