#pragma once
#include "piezas/pieza.h"

struct Nodo {
	Pieza* pieza;
	Nodo* siguiente;

	Nodo(Pieza* p) : pieza(p), siguiente(nullptr) {}
};

class listapieza
{
	Nodo* cabeza;

public:
	listapieza() : cabeza(nullptr) {}
	~listapieza(); // se destruyen todas las piezas

	void agregar(Pieza* p);
	void eliminarMuertas();
	Nodo* getCabeza() const { return cabeza; }
};
