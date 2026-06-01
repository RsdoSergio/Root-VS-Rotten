#include "piezatierra.h"

void PiezaTierra::moverArena(DirArena dir, double xMin, double xMax, double yMin, double yMax)
{
    static constexpr double factor = 0.12;
    static constexpr double margen = 1.2;

    double paso = velocidad * factor;
    double x = posArena.getX();
    double y = posArena.getY();

    if (dir == DirArena::ARRIBA)    y += paso;
    if (dir == DirArena::ABAJO)     y -= paso;
    if (dir == DirArena::IZQUIERDA) x -= paso;
    if (dir == DirArena::DERECHA)   x += paso;

    if (x < xMin + margen) x = xMin + margen;
    if (x > xMax - margen) x = xMax - margen;
    if (y < yMin + margen) y = yMin + margen;
    if (y > yMax - margen) y = yMax - margen;

    posArena.setValores(x, y);

}