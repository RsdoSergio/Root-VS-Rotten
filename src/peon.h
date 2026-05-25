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

    void dibujaTablero(float x, float y) const override {}
    std::string getNombre() const override {
        return bando == Bando::planta ? "Seta Solar" : "Zombi";
    }
    void usarAtaqueSecundario() override {};
};