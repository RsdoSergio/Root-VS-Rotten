#pragma once
#include "pieza.h"
#include <string>
#include "ETSIDI.h"
#include "proyectil.h"
#include <cstdlib> //para el uso de la funcion rand
#include"caja.h"
#include"arena_constantes.h"
#include<vector>
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

	std::vector<Proyectil*> proyectil1;  // proyectiles del jugador 1
	std::vector<Proyectil*> proyectil2;  // proyectiles del jugador 2
	double tiempoDisparo1 = 0.0;        // tiempo acumulado desde ultimo disparo J1
	double tiempoDisparo2 = 0.0;        // tiempo acumulado desde ultimo disparo J2

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;
	void dibujaProyectiles() const;

	bool plantaGano = false; // true si ganó la planta, false si ganó el zombi

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
	void desactiva() {
		activo = false;
		pieza1 = nullptr;
		pieza2 = nullptr;
	}
	bool estaActiva() const { return activo; }
	void fDatos(Pieza& p1, Pieza& p2, BandoVentaja ventaja);

	void MoverPiezaZombi(int key);
	void MoverPiezaPlanta(unsigned char key);

	void recibirMovimiento(int jugador, int dir, bool estado);
	bool getPlantaGano() const { return plantaGano; } // getter para mundo
	
};