#include "valquiria.h"
#include "gestorTexturas.h"

std::string Valquiria::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/rotinabo.png"
        : "imagenes/sprites_zombies/zombie_globo.png";
}

