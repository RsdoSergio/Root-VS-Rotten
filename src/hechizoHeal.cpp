#include "hechizoHeal.h"
#include "tablero.h"
#include "pieza.h"

bool hechizoHeal::ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) {

    Pieza* Objetivo = tablero.getPieza(objetivo);

    if (Objetivo == nullptr) return false;
    if (Objetivo->getBando() != caster->getBando()) return false;

    Objetivo->curar(Objetivo->getVidaMax());
    return true;

}