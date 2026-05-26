#pragma once
#include "piezaTierra.h"
#include"proyectil.h"

// Pieza con ataque a distancia, vida media
class Arquero : public PiezaTierra {
    double velocidadProyectil;
public:
    
    Arquero(Bando b, Pos pos)
        : PiezaTierra(
            8.0,   // PV bajo
            5.0,   // Daño medio
            4.5,   // Vel. movimiento media
            0.6,   // Enfriamiento bajo
            b, pos),
        velocidadProyectil(8.0) {} // El proyectil viaja más rápido que la propia pieza

    double getVelocidadProyectil() const { return velocidadProyectil; }

    void getColorTablero(float& r, float& g, float& b) const override {
        if (bando == Bando::planta) { r = 0.95f; g = 0.95f; b = 0.2f; }
        else { r = 0.6f;  g = 0.6f;  b = 0.1f; }
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Guisantralladora" : "Pertigador";
    }
    void usarAtaqueSecundario() override {};
};