#pragma once
#include "pieza.h"

// Piezas que se mueven por casillas adyacentes, sin diagonal, sin saltar ocupadas
class PiezaTierra : public Pieza {
public:
    PiezaTierra(double vida, double fuerza, double vel, double intervalo, int radio, Bando b, Pos pos)
        : Pieza(vida, fuerza, vel, intervalo, radio, b, pos) {}

    TipoMovimiento getTipoMovimiento() const override {
        return TipoMovimiento::TIERRA;
    }

    bool tecla_arriba = false;  
    bool tecla_abajo = false;
    bool tecla_izq = false;
    bool tecla_dcha = false;

    int ultimo_eje_reciente = 0; // 0 = X fue lo último pulsado, 1 = Y fue lo último

    int  ultimo_eje_x = 0;   // -1 izq, 0 nada, +1 dcha  — última tecla X pulsada
    int  ultimo_eje_y = 0;   // -1 abajo, 0 nada, +1 arriba — última tecla Y pulsada

    void setMovimiento(int dir, bool estado);
    void actualizarArena(double dt, double xMin, double xMax, double yMin, double yMax);

    void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) override;
};
