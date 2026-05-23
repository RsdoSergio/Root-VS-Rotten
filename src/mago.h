#pragma once
#include "piezaTeletransporte.h"
#include <array>

enum class Hechizo {
    TELEPORT,
    HEAL,
    REVIVE,
    IMPRISON,
    SHIFT_TIME,
    EXCHANGE,
    SUMMON
};

class Mago : public PiezaTeletransporte {
    double velocidadProyectil;
    std::array<bool, 7> hechizosUsados = { false };

public:
    Mago(Bando b, Pos pos)
        : PiezaTeletransporte(
            16.0,  // PV medio
            7.0,   // Daño medio
            4.0,   // Vel. movimiento media
            0.8,   // Enfriamiento medio
            b, pos),
        velocidadProyectil(6.0) {}

    double getVelocidadProyectil() const { return velocidadProyectil; }

    bool puedeUsarHechizo(Hechizo h) const {
        return !hechizosUsados[static_cast<int>(h)];
    }
    void usarHechizo(Hechizo h) {
        hechizosUsados[static_cast<int>(h)] = true;
    }

    void dibujaTablero(float x, float y) const override {}
    std::string getNombre() const override {
        return bando == Bando::planta ? "Girasol Primitivo" : "Doctor Zombie";
    }
    void usarAtaqueSecundario() override {};
};