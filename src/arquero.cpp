#include "arquero.h"
#include "gestorTexturas.h"

std::string Arquero::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/guisantralladora.png"
        : "imagenes/sprites_zombies/zombie_pertiga.png";
}


