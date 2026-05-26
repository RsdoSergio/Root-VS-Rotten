#pragma once
#include "piezaVuelo.h"

class Fenix : public PiezaVuelo {
    bool poderUsado = false; // Revive una vez con 15% PV, x1.5 vel y x2 daño durante 5s

public:
    Fenix(Bando b, Pos pos)
        : PiezaVuelo(
            14.0,  // PV medio
            8.0,   // Daño área
            6.0,   // Vel. movimiento alta
            1.0,   // Enfriamiento medio
            5, //rad de mov
            b, pos) {}

    bool puedeUsarPoder() const { return !poderUsado; }
    void usarPoder() { poderUsado = true; }

    void dibujaTablero(float x, float y) const override {
        // Naranja para LUZ, naranja oscuro para OSCURIDAD
        if (bando == Bando::planta) glColor3f(0.95f, 0.6f, 0.1f);
        else                     glColor3f(0.6f, 0.3f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Boca de Dragon" : "Zombidito Dragon";
    }
    void usarAtaqueSecundario() override {};
};
