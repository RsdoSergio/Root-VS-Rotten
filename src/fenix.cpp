#include "fenix.h"
#include "gestorTexturas.h"

std::string Fenix::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/boca_de_dragon.png"
        : "imagenes/sprites_zombies/zombie_dragon.png";
}

void Fenix::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Fenix::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
