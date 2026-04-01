#pragma once
#include<vector>
#include<iostream>
#include "tablero/tablero.h"
#include "pieza.h"

class Mundo
{
	Tablero tablero;
	
	std::vector<Pieza> Planta;
	std::vector<Pieza> Zombi;

public:
	void inicializa();
	void dibuja();
	void mueve();
	void tecla(unsigned char key);
};