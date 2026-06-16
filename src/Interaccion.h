#pragma once
#include "pieza.h"
#include "caja.h"
#include "proyectil.h"

class Interaccion
{
public:
    static void choque(Pieza& p, const Caja& c);
    static void choque(Proyectil& pr, Pieza& p);
};