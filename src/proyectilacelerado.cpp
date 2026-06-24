#include "proyectilacelerado.h"

void ProyectilAcelerado::mueve(double dt)
{
    if (!getEstado()) return;

    tiempoVidaLocal += dt;

    // curva senoidal: 0 en los extremos, pico en el centro
    double t = tiempoVidaLocal / duracionTotal;
    double vel = velMin + (velMax - velMin) * (1.0 - t);

    posicion = posicion + Vector2D(dirX * vel * dt, dirY * vel * dt);

    if (tiempoVidaLocal >= duracionTotal)
        desactivar();
}
