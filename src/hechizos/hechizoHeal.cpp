#include "hechizoHeal.h"
#include "tablero.h"
#include "piezas/pieza.h"

bool hechizoHeal::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
	Pieza* destino = tablero.getPieza(objetivo);

	if (destino == nullptr) return false;                      // casilla vacia
	if (destino->getBando() != caster->getBando()) return false; // no es aliado

	destino->curar(destino->getVidaMax()); // cura al maximo
	return true;
}
