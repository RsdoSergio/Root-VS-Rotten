#include "valquiria.h"
#include "gestorTexturas.h"

std::string Valquiria::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/rotinabo.png"
        : "imagenes/sprites_zombies/zombie_globo.png";
}

void Valquiria::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Valquiria::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
