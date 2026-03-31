#pragma once

// Dimensiones del tablero
const int FILAS = 9;
const int COLS = 9;
const float TAM_CELDA = 2.8f;

// Tipos de casilla
enum TipoCasilla {
	NORMAL,
	POWER_LIGHT,   // casillas especiales de Root (plantas)
	POWER_DARK     // casillas especiales de Rotten (zombies)
};

// Struct que representa una casilla
struct Casilla {
	TipoCasilla tipo;
	bool ocupada;
};

// El tablero completo
struct Tablero {
	Casilla casillas[FILAS][COLS];
};

// Funciones
void inicializaTablero(Tablero& t);
void dibujaTablero(const Tablero& t);