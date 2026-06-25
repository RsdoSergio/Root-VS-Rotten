#include "mago.h"
#include "gestorTexturas.h"

std::string Mago::getRutaSprite() const
{
    if (transformado)
        return bando == Bando::planta
        ? "" // pendiente: hay que implementar el sprite
        : "";  // pendiente: hay que implementar el sprite
}