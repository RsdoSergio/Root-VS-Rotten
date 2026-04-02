#pragma once
#include "pared.h"
#include "pieza.h"

const double ancho = 45; 
const double alto = 25.2; //calculo 9*2.8=25.2, para que las paredes queden justo en los bordes del tablero
const double a_2 = ancho / 2;
const double h_2 = alto / 2;
const double h_HUD = 6.0;


class caja
{
    pared suelo{ {-a_2, -h_2}, {a_2, -h_2}, {255, 255, 255} };
    pared techo{ {-a_2, h_2}, {a_2, h_2}, {255, 255, 255} };
    pared izquierda{ {-a_2, -h_2}, {-a_2, h_2}, {255, 255, 255} };
    pared derecha{ {a_2, -h_2}, {a_2, h_2}, {255, 255, 255} };

    double vida1, vidamax1, vida2, vidamax2;
	std::string nombre1, nombre2;

	void dibujaHUD();

public:
	caja() = default;

	void dibuja();
	void fDatos(const pieza& p1, const pieza& p2);
};

