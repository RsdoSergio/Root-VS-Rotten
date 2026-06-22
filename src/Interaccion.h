#pragma once
#include "piezas/pieza.h"
#include "caja.h"
#include "proyectil.h"
#include "obstaculo.h"

class Interaccion
{
public:
	static void choque(Pieza& p, const Caja& c);
	static void choque(Proyectil& pr, Pieza& p);
	static void choque(Pieza& p, const Obstaculo& o);
	static void choque(Pieza& p1, Pieza& p2);
	static void choque(Proyectil& pr, const Obstaculo& o);
};