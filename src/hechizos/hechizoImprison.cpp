#include "hechizoImprison.h"
#include "tablero.h"
#include "piezas/pieza.h"

bool hechizoImprison::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
	Pieza* enemigo = tablero.getPieza(objetivo);

	if (enemigo == nullptr) return false;                       // casilla vacia
	if (enemigo->getBando() == caster->getBando()) return false; // no es enemigo

	enemigo->aprisionar(tablero.getTurnoActual());
	return true;
}