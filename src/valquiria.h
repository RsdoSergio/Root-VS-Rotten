#pragma once
#include "piezaVuelo.h"

class Valquiria : public PiezaVuelo {
    double velocidadProyectil; // Proyectil rápido, menos daño. También tiene ráfaga

public:
    Valquiria(Bando b, Pos pos)
        : PiezaVuelo(
            10.0,  // PV medio
            2.0,   // Daño bajo por proyectil (compensa con ráfaga)
            6.5,   // Vel. movimiento muy alta
            0.2,   // Enfriamiento ráfaga muy bajo
            4,//rad de mov
            b, pos),
        velocidadProyectil(8.0) {}

    double getVelocidadProyectil() const { return velocidadProyectil; }

    void dibujaTablero(float x, float y) const override {
        // Cian para LUZ, azul oscuro para OSCURIDAD
        if (bando == Bando::planta) glColor3f(0.2f, 0.9f, 0.9f);
        else                     glColor3f(0.1f, 0.3f, 0.7f);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Rotinabo" : "Globador";
    }
    void usarAtaqueSecundario() override {};
};