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


void Pieza::setDireccion(DirMovimiento d) {
    dirActual = d;
    switch (d) {
    case DirMovimiento::ESTE:  ultimo_eje_x = +1; ultimo_eje_y = 0; break;
    case DirMovimiento::OESTE: ultimo_eje_x = -1; ultimo_eje_y = 0; break;
    case DirMovimiento::NORTE: ultimo_eje_x = 0; ultimo_eje_y = +1; break;
    case DirMovimiento::SUR:   ultimo_eje_x = 0; ultimo_eje_y = -1; break;
    default: break; // IDLE no toca los ejes
    }
}

void Pieza::resetEjes() {
    ultimo_eje_x = 0;
    ultimo_eje_y = 0;
    ultimo_eje_reciente = 0;
}