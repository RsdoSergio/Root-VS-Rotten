#pragma once
#include "pos.h"	
#include <string>

class Tablero;
class Pieza;

class Hechizo
{
	virtual ~Hechizo() {}

	virtual bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) = 0;
};