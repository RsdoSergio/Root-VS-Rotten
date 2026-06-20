#pragma once
#include "pieza.h"
#include "caja.h"
#include "proyectil.h"
#include "obstaculo.h"

class Interaccion
{
public:
	static void choque(Pieza& p, const Caja& c);
	static void choque(Proyectil& pr, Pieza& p);
	static void choque(Pieza& p, const Obstaculo& o);
};