#include "arquero.h"
#include "gestorTexturas.h"

Proyectil* Arquero::crearProyectil(int dirX, int dirY)
{
	double len = std::sqrt((double)(dirX * dirX + dirY * dirY));
	double ndx = dirX / len;
	double ndy = dirY / len;
	return new ProyectilAcelerado(getPosArena(), ndx, ndy, getFuerza(), DURACION_PROYECTIL, VEL_MIN, VEL_MAX, getRutaProyectil());
}