#pragma once
#include "pieza.h"
#include <string>
#include "ETSIDI.h"
#include "proyectil.h"
#include "arena_constantes.h"
#include"caja.h"
#include <cstdlib> //para el uso de la funcion rand

using namespace std;

constexpr double ARENA_ANCHO = 44.0;
constexpr double ARENA_ALTO = 26.0;
constexpr double SEMIANCHO = ARENA_ANCHO / 2.0;
constexpr double SEMIALTO = ARENA_ALTO / 2.0;
constexpr double HUD_ALTO = 1.0;
constexpr double HUD_BASE = SEMIALTO - HUD_ALTO;
constexpr double HUD_TECHO = SEMIALTO;
constexpr double VEL_PROYECTIL = 12.0;

constexpr double MARGEN = 1.5;
constexpr double MARGEN_INF = 4;

class arena
{
	bool activo = false;

	string nombrePieza1{};
	string nombrePieza2{};
	double vidaPieza1 = 0.0;
	double vidaPieza2 = 0.0;
	double vidaMaxPieza1 = 1.0;
	double vidaMaxPieza2 = 1.0;

	// Punteros a las piezas que combaten (para dibujarlas)
	 Pieza* pieza1 = nullptr;
	 Pieza* pieza2 = nullptr;
	 // Se usa un puntero para poder tenerlo o no
	 Proyectil* proyectil1 = nullptr;  // Q
	 Proyectil* proyectil2 = nullptr;  // K

	 Caja caja;

 

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;
	void dibujaProyectiles() const;

	int indiceFondo = 1; //para el fondo

public:
	arena() {};

	void dibuja() const;
	void mueve(double dt);           // mueve los proyectiles activos
	void tecla(unsigned char key);   // q dispara pieza1, k dispara pieza2

	void activa()
	{
		activo = true;
		indiceFondo = 1 + rand() % 9;
	}
	void desactiva() { activo = false; }
	bool estaActiva() const { return activo; }
	void fDatos(const Pieza& p1, const Pieza& p2);
};
