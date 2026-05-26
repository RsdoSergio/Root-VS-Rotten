#pragma once
#include "piezaVuelo.h"

class Valquiria : public PiezaVuelo {
    double velocidadProyectil; // Proyectil rápido, menos daño. También tiene ráfaga

public:
    Valquiria(Bando b, Pos pos)
        : PiezaVuelo(
            10.0,  // PV medio
            2.0,   // Daño bajo por proyectil (compensa con ráfaga)
            6.5,   // Vel. movimiento muy alta
            0.2,   // Enfriamiento ráfaga muy bajo
            b, pos),
        velocidadProyectil(8.0) {}

    double getVelocidadProyectil() const { return velocidadProyectil; }

    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.2f; g = 0.9f; b = 0.9f; }
        else { r = 0.1f; g = 0.3f; b = 0.7f; }
    }
    std::string getNombre() const override {
        return bando == Bando::planta ? "Rotinabo" : "Globador";
    }
    void usarAtaqueSecundario() override {};
};