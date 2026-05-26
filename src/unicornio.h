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

    double getVelocidadProyectil() const { return velocidadProyectil; }

    void dibujaTablero(float x, float y) const override {
        // Rosa claro para LUZ, rosa oscuro para OSCURIDAD
        if (bando == Bando::planta) glColor3f(0.95f, 0.7f, 0.8f);
        else                     glColor3f(0.6f, 0.3f, 0.4f);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }


    std::string getNombre() const override {
        return bando == Bando::planta ? "Rabano Casillero" : "Zombidito Momia";
    }
    void usarAtaqueSecundario() override {};
};