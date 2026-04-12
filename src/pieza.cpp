#include "pieza.h"
#include"vector2d.h"


Pieza::Pieza(TipoPieza t, double v, double f, double px, double py)
{
	posicion.setValores(px, py);
	velocidadPieza.setValores(0.0, 0.0);
}

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


void Pieza::setVida(double v)
{
	//comprobacion de que la vida de la pieza esta en valores coherentes (0<vida<100)
	if (v <= 0)v = 0;
	
	if (v >= 100)v = 100; //revisar y comprobar parametro de MAX VIDA
	
	vida = v;

}

void Pieza::setVelpieza(double x, double y)
{
	velocidadPieza.setValores(x, y);


}






