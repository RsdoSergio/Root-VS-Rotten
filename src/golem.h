#pragma once
#include "piezaTierra.h"

// Pieza lenta y muy resistente, golpe fuerte cuerpo a cuerpo
class Golem : public PiezaTierra {
public:
    Golem(Bando b, Pos pos)
        : PiezaTierra(
            24.0, // vida muy alta
            10.0,  // fuerza alta
            3.0,   // velocidad baja
           1.2,   // recarga lenta
            b, pos) {}

    void dibujaTablero(float x, float y) const override {
        // Marrón claro para LUZ, marrón oscuro para OSCURIDAD
        if (bando == Bando::planta) glColor3f(0.8f, 0.6f, 0.3f);
        else                     glColor3f(0.5f, 0.3f, 0.1f);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }


    std::string getNombre() const override {
        return bando == Bando::planta ? "Bonk Choy" : "Yeti";
    }
    void usarAtaqueSecundario() override {};
};