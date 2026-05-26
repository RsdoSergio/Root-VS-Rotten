#pragma once
#include "piezaTierra.h"

// Pieza básica: rápida pero débil. Bando LUZ = Planta, Bando OSCURIDAD = Zombi
class Peon : public PiezaTierra {
public:
    Peon(Bando b, Pos pos)
        : PiezaTierra(
            12.0,  // vida baja
            4.0,   // fuerza baja
            5.0,   // velocidad alta
            0.4,   // recarga rápida
            b, pos) {}

    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.84f; g = 1.0f;  b = 0.39f; }
        else { r = 0.39f; g = 0.46f; b = 0.18f; }
    }
    std::string getNombre() const override {
        return bando == Bando::planta ? "Seta Solar" : "Zombi";
    }
    void usarAtaqueSecundario() override {};

   
};