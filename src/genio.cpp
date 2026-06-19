#include "genio.h"
#include "gestorTexturas.h"

std::string Djinn::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/mazorcanon.png"
        : "imagenes/sprites_zombies/zombie_gondola.png";
}

void Djinn::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Djinn::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}
