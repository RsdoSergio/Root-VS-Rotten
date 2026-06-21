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
            4, //rad de mov
            b, pos),
        velocidadProyectil(6.0) {} // Proyectil medio

    double getVelocidadProyectil() const override { return velocidadProyectil; }

    // Antes se dibujaba como cuadrado de color (rosa claro LUZ / rosa oscuro OSCURIDAD);
    // ahora usa sprite, ver Unicornio::getRutaSprite() en unicornio.cpp
    std::string getRutaSprite() const override;
    


    std::string getNombre() const override {
        return bando == Bando::planta ? "Rabano Casillero" : "Zombidito Momia";
    }
    void usarAtaqueSecundario() override {};
};