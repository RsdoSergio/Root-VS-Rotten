#pragma once
#include "piezas/pieza.h"
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
#include "tablero.h"


constexpr int MAX_OBSTACULOS = 6;

class arena
{
	bool activo = false;

	std::string nombrePieza1{};
	std::string nombrePieza2{};
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

	Obstaculo obstaculos[MAX_OBSTACULOS];
	int numObstaculos = 0;

	void dibujaFondo() const;
	void dibujaInterior() const;
	void dibujaMarco() const;
	void dibujaHUD() const;
	void dibujaPiezasArena() const;
	void dibujaProyectiles() const;
	void dibujaObstaculos()  const;
	void colocarObstaculoAleatorio(int indice);

	bool plantaGano = false; // true si ganó la planta, false si ganó el zombi
	bool terminado = false;  // true si el combate ya acabo pero seguimos esperando al barrido

	int indiceFondo = 1; //para el fondo

	int indiceCombate = 0;        // 0=normal, 1=20%, 2=40%, 3=60%, 4=80%, 5=100% (para la ambientación circustancial)
	bool musicaViolentaActiva = false;

	double intervaloOriginal1 = 0.0;
	double intervaloOriginal2 = 0.0;
	double vidaMaxOriginal1 = 0.0;
	double vidaMaxOriginal2 = 0.0;
	double fuerzaOriginal1 = 0.0;
	double fuerzaOriginal2 = 0.0;
	float velocidadOriginal1 = 0.0f;
	float velocidadOriginal2 = 0.0f;



public:
	arena() {};

	void dibuja() const;
	void mueve(double dt);           // mueve los proyectiles activos
	void tecla(unsigned char key);   // q dispara pieza1, k dispara pieza2

	void activa();

	void desactiva();

	bool estaActiva() const { return activo; }
	void fDatos(Pieza& p1, Pieza& p2, BandoVentaja ventaja, bool boost1, bool boost2, int poderPlanta, int poderZombi);

	void recibirMovimiento(int jugador, int dir, bool estado);
	void procesarAtaque(Pieza* p, std::vector<Proyectil*>& proyectiles, double& tiempoDisparo, int dirDefecto);
	bool getPlantaGano() const { return plantaGano; } // getter para mundo

	void aplicarDanoExplosiones();

	bool combateTerminado() const { return terminado; }

	bool boostPieza1 = false; // pieza1 estaba en casilla de poder
	bool boostPieza2 = false; // pieza2 estaba en casilla de poder

	void dibujaOverlayCombate() const;
};