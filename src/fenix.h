#pragma once
#include "piezaVuelo.h"

class Fenix : public PiezaVuelo {
    bool poderUsado = false; // Revive una vez con 15% PV, x1.5 vel y x2 daño durante 5s

public:
    Fenix(Bando b, Pos pos)
        : PiezaVuelo(
            14.0,  // PV medio
            8.0,   // Daño área
            6.0,   // Vel. movimiento alta
            1.0,   // Enfriamiento medio
            b, pos) {}

    bool puedeUsarPoder() const { return !poderUsado; }
    void usarPoder() { poderUsado = true; }

    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.95f; g = 0.6f; b = 0.1f; }
        else { r = 0.6f;  g = 0.3f; b = 0.0f; }
    }
    std::string getNombre() const override {
        return bando == Bando::planta ? "Boca de Dragon" : "Zombidito Dragon";
    }
    void usarAtaqueSecundario() override {};
};
