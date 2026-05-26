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
    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.8f; g = 0.6f; b = 0.3f; }
        else { r = 0.5f; g = 0.3f; b = 0.1f; }
    }


    std::string getNombre() const override {
        return bando == Bando::planta ? "Bonk Choy" : "Yeti";
    }
    void usarAtaqueSecundario() override {};
};