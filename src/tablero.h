#pragma once
#include "casilla.h"
#include"pos.h"
#include<vector>
#include "listapieza.h"

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
	bool piezaBloqueada(Pos p);

	bool gestionarEntrada(Pos cursor, int& turno);
	void cancelarSeleccion();
	void dibuja(const Cursor& cursor);

	// Getters para que Mundo pueda acceder a los combatientes
	Pieza* getPersonaje1() const { return personaje1; }
	Pieza* getPersonaje2() const { return personaje2; }

private:

	void dibujaTablero(const Cursor& cursor);
	void dibujaPiezas();
	void marcaCasillasValidas();

	Casilla casillas[FILAS][COLS];
	Pos piezaSeleccionada;
	std::vector<Pos> casillasValidas;
	bool movimientoPendiente = false;

	// Piezas involucradas en el ultimo combate detectado
	Pieza* personaje1 = nullptr;
	Pieza* personaje2 = nullptr;

	Pos posOrigen;
	Pos posDestino;

	std::vector<Pos> movimientosValidos(Pos origen);
	bool moverPieza(Pos origen, Pos destino);
};