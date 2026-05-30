#pragma once
#include"vector2d.h"
#include<cstdbool>
class Proyectil
{
    Vector2D posicion;
    Vector2D velocidad;
    double damage;
    bool activo; // Para saber si borrarlo cuando choque
    
public:
    Proyectil(Vector2D pos, Vector2D vel, double d)
        : posicion(pos), velocidad(vel), damage(d), activo(true) {}
    Vector2D getPosProyectil()const;
    Vector2D getVelProyectil()const;
    double getDamageProyectil()const;
    bool getEstado()const;

	void desactivar() { activo = false; }// Para marcarlo como inactivo cuando choque con algo
    //habra que implementarlo posteriormente

	//nuevos atributos y metodos para el movimiento y dibujo del proyectil
    void mueve(double dt);
    void dibuja() const;
    

};

