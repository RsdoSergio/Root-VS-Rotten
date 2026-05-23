#pragma once
#include "pieza.h"

// Piezas que pueden moverse a cualquier casilla válida del tablero instantáneamente
class PiezaTeletransporte : public Pieza {
public:
    PiezaTeletransporte(double vida, double fuerza, double vel, double intervalo, Bando b, Pos pos)
        : Pieza(vida, fuerza, vel, intervalo, b, pos) {}
};