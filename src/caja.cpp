#include "caja.h"

void Caja::dibuja  () const
{
    izq.dibuja();
    dcha.dibuja();
    suelo.dibuja();
    techo.dibuja();
}