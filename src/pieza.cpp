#include "pieza.h"
#include "freeglut.h"
#include <cmath>

Pieza::Pieza(double v, double f, double vel, double intervalo, Bando b, Pos pos)
    : vida(v), vidaMax(v),
    fuerza(f),
    velocidad(vel),
    intervaloAtaque(intervalo),
    bando(b),
    casilla(pos)
{
    posArena.setValores(0.0, 0.0);
}

void Pieza::recibirDanio(double d) {
    vida -= d;
    if (vida < 0.0) vida = 0.0;
}

void Pieza::curar(double cantidad) {
    vida += cantidad;
    if (vida > vidaMax) vida = vidaMax;
}

//ahora la pieza se dibuja directamente en pieza.cpp, se mantiene la funiconalidad de getColor hasta que se añadan los sprites
void Pieza::dibujaTablero(float x, float y) const
{
    float r, g, b;
    getColorTablero(r, g, b);

    glColor3f(r, g, b);
    glTranslatef(x, y, 0);
    glutSolidSphere(TAM_PIEZA, 15, 15);
    glTranslatef(-x, -y, 0);   // deshacer la translacion para no afectar al resto
}