#include "genio.h"
#include "gestorTexturas.h"

std::string Djinn::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/mazorcanon.png"
        : "imagenes/sprites_zombies/zombie_gondola.png";
}

