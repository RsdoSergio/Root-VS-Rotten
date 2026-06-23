#include "mago.h"
#include "gestorTexturas.h"

std::string Mago::getRutaSprite() const
{
    if (transformado)
        return bando == Bando::planta
        ? "" // pendiente: hay que implementar el sprite
        : "";  // pendiente: hay que implementar el sprite

    return bando == Bando::planta
        ? "imagenes/sprites_plantas/girasol_primitivo.png"
        : "imagenes/sprites_zombies/zombie_doctor.png";
}