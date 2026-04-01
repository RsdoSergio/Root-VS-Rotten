#include "pieza.h"



double Pieza::getVida() const
{
	return vida;
}

double Pieza::getFuerza() const
{
	return fuerza;
}

Vector2D Pieza::getPosicion() const
{
	return posicion;
}

Vector2D Pieza::getVelpieza() const
{
	return velocidadPieza;
}

Vector2D Pieza::getVelproyectil() const
{
	return velocidadProyectil;
}

void Pieza::setVida(double v)
{
	//comprobacion de que la vida de la pieza esta en valores coherentes (0<vida<100)
	if (v <= 0)v = 0;
	
	if (v >= 100)v = 100; //revisar y comprobar parametro de MAX VIDA
	
	vida = v;

}






