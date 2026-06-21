#pragma once
#include <vector>
#include <iostream>
#include "tablero.h"
#include "cursor.h"
#include "pos.h"
#include "arena.h"
#include "listapieza.h"
#include "piezas/pieza.h"
#include "piezas/peon.h"
#include "menu.h"
#include "caja.h"
#include "gestorTexturas.h"
#include "piezas/mago.h"
#include "hechizos/hechizoHeal.h"

class Mundo
{
	Tablero tablero;
	Cursor cursor{ 4, 4, 255, 220,   0 };  // amarillo
	Cursor cursor2{ 4, 4, 180,   0, 255 };  //morado
	listapieza ListaPieza;
	int     turno = 0;
	std::vector<Pos> casillasValidas;
	arena arena;
	Menu    menu;
	bool    enPartida = false;
	bool    enPausa = false;
	Caja caja;
	int opcionPausa = 0;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
	void teclaEspecial(int key);   // flechas del teclado para cursor2
	void clicRaton(int boton, int estado, int xPixel, int yPixel); // clic de raton sobre el tablero
	//funciones para gestionar el pulsado continuo de tecla
	void teclaLevantada(unsigned char key);
	void teclaEspecialLevantada(int key);

private:
	void jugarCasilla(Pos casilla); // logica comun: seleccionar/mover pieza en esa casilla del turno actual
	hechizoHeal hechizoHeal;
	Pieza* magoSeleccionado = nullptr;
	//std::string textoHechizos() const;
};
