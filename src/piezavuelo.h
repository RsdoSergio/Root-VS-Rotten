#pragma once
#include "pieza.h"

// Piezas que se mueven libremente sin restricciones de dirección ni piezas en medio
class PiezaVuelo : public Pieza {
public:
    PiezaVuelo(double vida, double fuerza, double vel, double intervalo, int radio, Bando b, Pos pos)
        : Pieza(vida, fuerza, vel, intervalo, radio, b, pos) {}
};