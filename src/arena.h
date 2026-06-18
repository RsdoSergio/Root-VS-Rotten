#pragma once
#include "pieza.h"
#include <string>
#include "ETSIDI.h"
#include "proyectil.h"
#include <cstdlib> //para el uso de la funcion rand
#include <ctime>
#include <cmath>
#include"caja.h"
#include"arena_constantes.h"
#include "obstaculo.h"
#include<vector>
using namespace std;

constexpr int NUM_OBSTACULOS = 5;

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

	Obstaculo obstaculos[NUM_OBSTACULOS];

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;
	void dibujaProyectiles() const;
	void dibujaObstaculos()  const;
	void colocarObstaculoAleatorio(Obstaculo& o, int i);
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

		for (int i = 0; i < NUM_OBSTACULOS; i++)
			colocarObstaculoAleatorio(obstaculos[i], i);
	}

	void desactiva()
	{
		activo = false;
		pieza1 = nullptr;
		pieza2 = nullptr;
	}

	bool estaActiva() const { return activo; }
	void fDatos(Pieza& p1, Pieza& p2);

	void recibirMovimiento(int jugador, int dir, bool estado);
};
