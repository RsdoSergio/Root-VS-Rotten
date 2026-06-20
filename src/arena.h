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
	bool ataqueMeleeActivo(Pieza* p, const std::vector<Proyectil*>& proyectiles) const;

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
		numObstaculos = 3 + rand() % 4;

		for (int i = 0; i < MAX_OBSTACULOS; i++)
			obstaculos[i].desactivar();

		for (int i = 0; i < numObstaculos; i++)
			colocarObstaculoAleatorio(i);
	}

	void desactiva()
	{
		//reseteo de la pieza a x defecto
		if (pieza1)
		{
			pieza1->setAccion(AccionPieza::IDLE);
			pieza1->setDireccion(DirMovimiento::IDLE);
		}
		if (pieza2)
		{
			pieza2->setAccion(AccionPieza::IDLE);
			pieza2->setDireccion(DirMovimiento::IDLE);
		}

		//limpia los proyectiles que hayan quedado activos al terminar el combate
		for (Proyectil* pr : proyectil1)
			delete pr;
		for (Proyectil* pr : proyectil2)
			delete pr;
		proyectil1.clear();
		proyectil2.clear();

		activo = false;
		pieza1 = nullptr;
		pieza2 = nullptr;
	}

	bool estaActiva() const { return activo; }
	void fDatos(Pieza& p1, Pieza& p2, BandoVentaja ventaja);

	void recibirMovimiento(int jugador, int dir, bool estado);
	void procesarAtaque(Pieza* p, std::vector<Proyectil*>& proyectiles, double& tiempoDisparo, int dirDefecto);
	bool getPlantaGano() const { return plantaGano; } // getter para mundo
	
};