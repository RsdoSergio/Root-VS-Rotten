#pragma once
#include "piezaTierra.h"

// Pieza lenta y muy resistente, golpe fuerte cuerpo a cuerpo
class Golem : public PiezaTierra {
public:
    Golem(Bando b, Pos pos)
        : PiezaTierra(
            24.0, // vida muy alta
            10.0,  // fuerza alta
            3.0,   // velocidad baja
           1.2,   // recarga lenta
            b, pos) {}

    void dibujaTablero(float x, float y) const override {}
    std::string getNombre() const override {
        return bando == Bando::planta ? "Bonk Choy" : "Yeti";
    }
    void usarAtaqueSecundario() override {};
};