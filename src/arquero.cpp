#include "arquero.h"
#include "gestorTexturas.h"

std::string Arquero::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/guisantralladora.png"
        : "imagenes/sprites_zombies/zombie_pertiga.png";
}

void Arquero::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Arquero::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
