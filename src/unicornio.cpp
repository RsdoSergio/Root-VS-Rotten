#include "unicornio.h"
#include "gestorTexturas.h"

std::string Unicornio::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/rabano_casillero.png"
        : "imagenes/sprites_zombies/zombie_momia.png";
}

void Unicornio::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Unicornio::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
