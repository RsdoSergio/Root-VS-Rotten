#pragma once
#include"vector2d.h"
#include<cstdbool>
#include <string>

class Proyectil
{
protected:

	friend class Interaccion;
	Vector2D posicion;
	Vector2D velocidad;
	double damage;
	bool activo; // Para saber si borrarlo cuando choque
	double duracion;
	double tiempoVivo;
	std::string rutaSprite;

public:
	Proyectil(Vector2D pos, Vector2D vel, double d, double duracion = -1.0, std::string ruta = "")
		: posicion(pos), velocidad(vel), damage(d), activo(true), duracion(duracion), tiempoVivo(0.0), rutaSprite(ruta) {}
	Vector2D getPosProyectil()const;
	Vector2D getVelProyectil()const;
	double getDamageProyectil()const;
	bool getEstado()const;

	void desactivar() { activo = false; }// Para marcarlo como inactivo cuando choque con algo
	//habra que implementarlo posteriormente

	//nuevos atributos y metodos para el movimiento y dibujo del proyectil
	virtual void mueve(double dt);
	void dibuja() const;
};
