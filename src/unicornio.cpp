#include "unicornio.h"
#include "gestorTexturas.h"

std::string Unicornio::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/rabano_casillero.png"
        : "imagenes/sprites_zombies/zombie_momia.png";
}

