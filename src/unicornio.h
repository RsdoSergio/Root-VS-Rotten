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

    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.95f; g = 0.7f; b = 0.8f; }
        else { r = 0.6f;  g = 0.3f; b = 0.4f; }
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Rabano Casillero" : "Zombidito Momia";
    }
    void usarAtaqueSecundario() override {};
};