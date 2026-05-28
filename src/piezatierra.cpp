#include "piezatierra.h"

void PiezaTierra::moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax)
{
    static constexpr double FACTOR = 0.12;
    static constexpr double MARGEN = 1.2;

    double paso = velocidad * FACTOR;
    double x = posArena.getX();
    double y = posArena.getY();

    if (dir == DirArena::ARRIBA)    y += paso;
    if (dir == DirArena::ABAJO)     y -= paso;
    if (dir == DirArena::IZQUIERDA) x -= paso;
    if (dir == DirArena::DERECHA)   x += paso;

    if (x < xMin + MARGEN) x = xMin + MARGEN;
    if (x > xMax - MARGEN) x = xMax - MARGEN;
    if (y < yMin + MARGEN) y = yMin + MARGEN;
    if (y > yMax - MARGEN) y = yMax - MARGEN;

    posArena.setValores(x, y);
}
