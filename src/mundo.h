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
#include "hechizos/hechizoRevive.h"
#include "hechizos/hechizoExchange.h"
#include "hechizos/hechizoHeal.h"
#include "hechizos/hechzoTeleport.h"
#include <string>
#include "piezas/mago.h"
#include "transicion.h"

enum class AccionTransicion {
	NINGUNA,
	EMPEZAR_PARTIDA,
	ABRIR_CARTEL_VERSUS,
	ABRIR_CARTEL_RESULTADO,
	CERRAR_CARTEL_VERSUS,
	CERRAR_CARTEL_RESULTADO
};

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

	Transicion transicion;
	AccionTransicion accionPendiente = AccionTransicion::NINGUNA;
	bool     mostrandoCartel = false;
	double   tiempoCartel = 0.0;
	std::string rutaCartel = "";
	AccionTransicion accionTrasCarte = AccionTransicion::NINGUNA;

	void jugarCasilla(Pos casilla); // logica comun: seleccionar/mover pieza en esa casilla del turno actual
	hechizoHeal hechizoHeal;
	Pieza* magoSeleccionado = nullptr;
	hechizoRevive hechizoRevive;
	bool eligiendoRevive = false;

	bool mostrarPanelHechizos = false;
	std::string mensajeFeedback;
	double tiempoFeedback = 0.0;

	std::string generarTextoPanel() const;
	void dibujaPanelHechizos() const;
	hechizoExchange hechizoExchange;
	bool eligiendoExchangeOrigen = false;
	hechizoTeleport hechizoTeleport;
	bool eligiendoTeleportOrigen = false;

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
};