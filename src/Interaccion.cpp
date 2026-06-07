#include "interaccion.h"

void Interaccion::choque(Pieza& p, const Caja& c)
{
    constexpr double radio = TAM_PIEZA / 2.0;

    double x = p.posArena.getX();
    double y = p.posArena.getY();

    if (x - radio < c.izq.limite1_.getX())   x = c.izq.limite1_.getX() + radio;
    if (x + radio > c.dcha.limite1_.getX())   x = c.dcha.limite1_.getX() - radio;
    if (y - radio < c.suelo.limite1_.getY())  y = c.suelo.limite1_.getY() + radio;
    if (y + radio > c.techo.limite1_.getY())  y = c.techo.limite1_.getY() - radio;

    p.posArena.setValores(x, y);
}