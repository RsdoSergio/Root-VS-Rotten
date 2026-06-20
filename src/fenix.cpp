#include "fenix.h"
#include "gestorTexturas.h"

std::string Fenix::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/boca_de_dragon.png"
        : "imagenes/sprites_zombies/zombie_dragon.png";
}

