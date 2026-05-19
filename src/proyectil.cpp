#include "proyectil.h"

Vector2D Proyectil::getPosProyectil() const 
{
    return posicion; // ← faltaba esto
}

Vector2D Proyectil::getVelProyectil() const 
{
    return velocidad; // ← faltaba esto
}

double Proyectil::getDamageProyectil() const 
{
    return damage; // ← faltaba esto
}

bool Proyectil::getEstado() const 
{
    return activo; // ← faltaba esto
}