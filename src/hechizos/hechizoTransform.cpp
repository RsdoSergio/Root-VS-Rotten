#include "hechizoTransform.h"
#include "tablero.h"
#include "piezas/mago.h"

bool hechizoTransform::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
	Mago* mago = dynamic_cast<Mago*>(caster);
	if (mago == nullptr) return false;

	mago->transformar();
	return true;
}