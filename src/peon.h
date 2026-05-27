#pragma once
#include "piezaTierra.h"

// Pieza básica: rápida pero débil. Bando LUZ = Planta, Bando OSCURIDAD = Zombi
class Peon : public PiezaTierra {
public:
    Peon(Bando b, Pos pos)
        : PiezaTierra(
            12.0,  // vida baja
            4.0,   // fuerza baja
            5.0,   // velocidad alta
            0.4,   // recarga rápida
            2, //rad de mov
            b, pos) {}

    void dibujaTablero(float x, float y) const override {
        // Verde claro para LUZ, gris verdoso para OSCURIDAD
        if (bando == Bando::planta) glColor3b(214, 255, 99);
        else                     glColor3b(99, 117, 47);
        glBegin(GL_POLYGON);
        glVertex3f(x - TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y - TAM_PIEZA, 0);
        glVertex3f(x + TAM_PIEZA, y + TAM_PIEZA, 0);
        glVertex3f(x - TAM_PIEZA, y + TAM_PIEZA, 0);
        glEnd();
    }

    std::string getNombre() const override {
        return bando == Bando::planta ? "Seta Solar" : "Zombi";
    }
    void usarAtaqueSecundario() override {};

   
};