#pragma once
#include "pieza.h"
#include <string>
#include "ETSIDI.h"
#include "proyectil.h"
#include "arena_constantes.h"
#include"caja.h"


using namespace std;




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

	 Caja caja;

	// Proyectil activo de cada bando 
	// Se usa un puntero para poder tenerlo o no
	Proyectil* proyectil1 = nullptr;  // Q
	Proyectil* proyectil2 = nullptr;  // K

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;
	void dibujaProyectiles() const;

public:
	arena() {};

	void dibuja() const;
	void mueve(double dt);           // mueve los proyectiles activos
	void tecla(unsigned char key);   // q dispara pieza1, k dispara pieza2

	void activa() { activo = true; }
	void desactiva() { activo = false; }
	bool estaActiva() const { return activo; }
	void fDatos( Pieza& p1,  Pieza& p2);

	void MoverPiezaPlanta(unsigned char key);
	void MoverPiezaZombi(int key);
	


};
