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

    void dibujaTablero(float x, float y) const override {
        // Dorado para LUZ, rojo oscuro para OSCURIDAD (son los líderes, destacan)
        if (bando == Bando::planta) glColor3f(1.0f, 0.85f, 0.0f);
        else                     glColor3f(0.7f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Girasol Primitivo" : "Doctor Zombie";
    }
    void usarAtaqueSecundario() override {};
};