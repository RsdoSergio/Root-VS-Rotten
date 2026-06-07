#pragma once
#include "pieza.h"
#include "caja.h"

class Interaccion
{
public:
    static void choque(Pieza& p, const Caja& c);
};