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

    int ultimo_eje_reciente = 0; // 0 = X fue lo último pulsado, 1 = Y fue lo último

    int  ultimo_eje_x = 0;   // -1 izq, 0 nada, +1 dcha  — última tecla X pulsada
    int  ultimo_eje_y = 0;   // -1 abajo, 0 nada, +1 arriba — última tecla Y pulsada

    void setMovimiento(int dir, bool estado);
    void actualizarArena(double dt);

    
};