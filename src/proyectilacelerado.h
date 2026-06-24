#pragma once
#include "proyectil.h"
#include <cmath>

constexpr double M_PI = 3.14159265359;


class ProyectilAcelerado : public Proyectil
{
    double velMin;
    double velMax;
    double duracionTotal;
    double tiempoVidaLocal = 0.0;
    double dirX, dirY; // dirección normalizada

public:
    ProyectilAcelerado(Vector2D pos, double dx, double dy,double dano, double duracion,double velocidadMin, double velocidadMax)
         :Proyectil(pos, Vector2D(0.0, 0.0), dano, duracion),
          velMin(velocidadMin), velMax(velocidadMax),
          duracionTotal(duracion), dirX(dx), dirY(dy) {}

    void mueve(double dt) override;
    
};

