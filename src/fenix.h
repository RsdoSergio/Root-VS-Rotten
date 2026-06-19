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
            5, //rad de mov
            b, pos) {}

    bool puedeUsarPoder() const { return !poderUsado; }
    void usarPoder() { poderUsado = true; }

    // Antes se dibujaba como cuadrado de color (naranja LUZ / naranja oscuro OSCURIDAD);
    // ahora usa sprite, ver Fenix::getRutaSprite() en fenix.cpp
    std::string getRutaSprite() const override;
    void dibujaTablero(float x, float y) const override;
    void dibujaArena(float x, float y) const override;

    std::string getNombre() const override {
        return bando == Bando::planta ? "Boca de Dragon" : "Zombidito Dragon";
    }
    void usarAtaqueSecundario() override {};
};
