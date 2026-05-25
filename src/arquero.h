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

    void dibujaTablero(float x, float y) const override {}
    std::string getNombre() const override {
        return bando == Bando::planta ? "Guisantralladora" : "Pertigador";
    }
    void usarAtaqueSecundario() override {};
};