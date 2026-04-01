#pragma once
#include "pared.h"
const double ancho = 45; //calculo 9*2.8=25.2, para que las paredes queden justo en los bordes del tablero
const double alto = 25.2;
const double a_2 = ancho / 2;
const double h_2 = alto / 2;
class caja
{
    pared suelo{ {-a_2, -h_2}, {a_2, -h_2}, {255, 255, 255} };
    pared techo{ {-a_2, h_2}, {a_2, h_2}, {255, 255, 255} };
    pared izquierda{ {-a_2, -h_2}, {-a_2, h_2}, {255, 255, 255} };
    pared derecha{ {a_2, -h_2}, {a_2, h_2}, {255, 255, 255} };

public:
	void dibuja();
};

