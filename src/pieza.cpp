#include "pieza.h"


Pieza::Pieza(double v, double f, double vel, double intervalo, int radio, Bando b, Pos pos)
    : vida(v), vidaMax(v),
    fuerza(f),
    velocidad(vel),
    intervaloAtaque(intervalo),
    radioMovimiento(radio), // ? nuevo
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