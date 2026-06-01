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

    bool mov_arriba = false;
    bool mov_abajo = false;
    bool mov_izq = false;
    bool mov_dcha = false;

    void setMovimiento(int dir, bool estado);
    void actualizarArena(double dt, double xMin, double xMax, double yMin, double yMax);

    void moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax) override;
};
