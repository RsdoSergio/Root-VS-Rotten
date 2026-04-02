#pragma once
#include"vector2d.h"
enum TipoPieza { peon, golem, archer, valquiria, djinn, unicornio, fenix, mago };
class Pieza
{
	TipoPieza tipo{peon};//etiqueta para saber que pieza es/ Lo inicializamos de manera temporal, luego cambiará al ser inicializado
	double vida{100.0};
	double fuerza{10.0};
	Vector2D posicion{};
	Vector2D velocidadPieza{};
	Vector2D velocidadProyectil{};

public:

	double getVida() const; //acceder al valor de la vida
	double getFuerza() const; //acceder al valor de la fuerza
	Vector2D getPosicion() const;//acceder al valor de la posicion
	Vector2D getVelpieza() const; //acceder al valor de la velocidad pieza
	Vector2D getVelproyectil() const;//acceder al valor de la velocidad proyectil
	
	TipoPieza getTipo() { return tipo; }
	void setTipo(TipoPieza t) { tipo = t; }
	


	void setVida(double v);//cambio en la vida de la pieza (curacion o recibir daño)
	void setFuerza(double f) { fuerza = f; }
	void setVelpieza(double x, double y);

};

