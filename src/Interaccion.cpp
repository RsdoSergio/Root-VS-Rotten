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

void Interaccion::choque(Proyectil& pr, Pieza& p)
{
    if (!pr.getEstado()) return; // ya desactivado, ignorar

    constexpr double radioPieza = TAM_PIEZA / 2.0;
    constexpr double radioProyectil = 0.1;
    double dx = pr.getPosProyectil().getX() - p.posArena.getX();
    double dy = pr.getPosProyectil().getY() - p.posArena.getY();
    double distancia = std::sqrt(dx * dx + dy * dy);
    if (distancia < (radioPieza + radioProyectil))
    {
        p.recibirDanio(pr.getDamageProyectil());
        pr.desactivar();
    }
}