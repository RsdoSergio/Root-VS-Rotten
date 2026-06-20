#pragma once
#include "piezaVuelo.h"

class Djinn : public PiezaVuelo {
    double velocidadProyectil; // Proyectil lento pero muy potente (one shot)

public:
    Djinn(Bando b, Pos pos)
        : PiezaVuelo(
            11.0,  // PV medio
            15.0,  // Daño muy alto
            5.5,   // Vel. movimiento alta
            2.5,   // Enfriamiento muy alto
            3, //rad de mov
            b, pos),
        velocidadProyectil(3.0) {} // Proyectil lento

    double getVelocidadProyectil() const override { return velocidadProyectil; }

    // Antes se dibujaba como cuadrado de color (morado claro LUZ / morado oscuro OSCURIDAD);
    // ahora usa sprite, ver Djinn::getRutaSprite() en genio.cpp
    std::string getRutaSprite() const override;
    

    std::string getNombre() const override {
        return bando == Bando::planta ? "Mazorcañon" : "Gondolero";
    }
    void usarAtaqueSecundario() override {};
};