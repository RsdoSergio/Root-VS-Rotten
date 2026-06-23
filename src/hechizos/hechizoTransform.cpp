#include "hechizoTransform.h"
#include "tablero.h"
#include "piezas/mago.h"

bool hechizoTransform::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
    // No necesita objetivo: el parametro 'objetivo' se ignora.
    Mago* mago = dynamic_cast<Mago*>(caster);
    if (mago == nullptr) return false;

    mago->transformar();
    return true;
}