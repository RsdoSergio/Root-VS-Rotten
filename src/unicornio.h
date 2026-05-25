#pragma once
#include "piezaTierra.h"

class Unicornio : public PiezaTierra {
    double velocidadProyectil; // Tiene proyectil además de melee

public:
    Unicornio(Bando b, Pos pos)
        : PiezaTierra(
            18.0,  // PV medio-alto
            6.0,   // Daño medio
            7.5,   // Vel. movimiento muy alta
            0.5,   // Enfriamiento bajo
            b, pos),
        velocidadProyectil(6.0) {} // Proyectil medio

    double getVelocidadProyectil() const { return velocidadProyectil; }

    void dibujaTablero(float x, float y) const override {}
    std::string getNombre() const override {
        return bando == Bando::planta ? "Rabano Casillero" : "Zombidito Momia";
    }
    void usarAtaqueSecundario() override {};
};