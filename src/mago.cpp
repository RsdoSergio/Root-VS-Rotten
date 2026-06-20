#include "mago.h"
#include "gestorTexturas.h"

std::string Mago::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/girasol_primitivo.png"
        : "imagenes/sprites_zombies/zombie_doctor.png";
}

