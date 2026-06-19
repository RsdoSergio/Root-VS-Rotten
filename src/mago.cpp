#include "mago.h"
#include "gestorTexturas.h"

std::string Mago::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/girasol_primitivo.png"
        : "imagenes/sprites_zombies/zombie_doctor.png";
}

void Mago::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Mago::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
