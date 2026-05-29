#pragma once
#include "pieza.h"
#include <string>
#include "ETSIDI.h"

using namespace std;

constexpr double ARENA_ANCHO = 44.0;
constexpr double ARENA_ALTO = 26.0;
constexpr double SEMIANCHO = ARENA_ANCHO / 2.0;
constexpr double SEMIALTO = ARENA_ALTO / 2.0;
constexpr double HUD_ALTO = 1.0;
constexpr double HUD_BASE = SEMIALTO - HUD_ALTO;
constexpr double HUD_TECHO = SEMIALTO;

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

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;

public:
	arena() {};

	void dibuja() const;
	void activa() { activo = true; }
	void desactiva() { activo = false; }
	bool estaActiva() const { return activo; }
	void fDatos( Pieza& p1,  Pieza& p2);
	void MoverPiezaPlanta(unsigned char key);
	void MoverPiezaZombi(int key);
	


};
