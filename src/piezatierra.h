#pragma once
#include "pieza.h"

// Piezas que se mueven por casillas adyacentes, sin diagonal, sin saltar ocupadas
class PiezaTierra : public Pieza {
public:
    PiezaTierra(double vida, double fuerza, double vel, double intervalo, Bando b, Pos pos)
        : Pieza(vida, fuerza, vel, intervalo, b, pos) {}
};
