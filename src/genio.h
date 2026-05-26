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
            b, pos),
        velocidadProyectil(3.0) {} // Proyectil lento

    double getVelocidadProyectil() const { return velocidadProyectil; }
    
    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.8f; g = 0.4f; b = 0.9f; }
        else { r = 0.4f; g = 0.1f; b = 0.5f; }
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Mazorcañon" : "Gondolero";
    }
    void usarAtaqueSecundario() override {};
};