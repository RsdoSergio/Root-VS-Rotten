#include "genio.h"
#include "gestorTexturas.h"

std::string Djinn::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/mazorcanon.png"
        : "imagenes/sprites_zombies/zombie_gondola.png";
}

Proyectil* Djinn::crearProyectil(int dirX, int dirY)
{
    {
        double len = std::sqrt((double)(dirX * dirX + dirY * dirY));
        double ndx = dirX / len;
        double ndy = dirY / len;
        return new ProyectilAcelerado(getPosArena(), ndx, ndy, getFuerza(), DURACION_PROYECTIL, VEL_MIN, VEL_MAX);

    }
}

