#pragma once
#include "pieza.h"

// Piezas que se mueven libremente sin restricciones de dirección ni piezas en medio
class PiezaVuelo : public Pieza {
public:
    PiezaVuelo(double vida, double fuerza, double vel, double intervalo, int radio, Bando b, Pos pos)
        : Pieza(vida, fuerza, vel, intervalo, radio, b, pos) {}

    TipoMovimiento getTipoMovimiento() const override {
        return TipoMovimiento::VUELO;
    }
    bool tecla_arriba = false;
    bool tecla_abajo = false;
    bool tecla_izq = false;
    bool tecla_dcha = false;

   

   

    void setMovimiento(int dir, bool estado);
    void actualizarArena(double dt);

    
};