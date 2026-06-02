#include "proyectil.h"
#include "freeglut.h"

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

void Proyectil::mueve(double dt)
{
    if (!activo) return;
	//todavia no hay aceleracion
    //se implmentara a posterior.
    posicion = posicion + velocidad * dt;
}

void Proyectil::dibuja() const
{
    //dibuja una esfera como proyectil
    if (!activo) return;
    glPushMatrix();
    glTranslated(posicion.getX(), posicion.getY(), 0);
    glColor3ub(255, 140, 0);
    glutSolidSphere(0.4, 12, 12);
    glPopMatrix();
}