#include "hechizoShiftTime.h"
#include "tablero.h"
#include "piezas/pieza.h"

bool hechizoShiftTime::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo)
{
    tablero.forzarVentajaPara(caster->getBando());
    return true;
}