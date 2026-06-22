#pragma once
#include "pos.h"	
#include <string>

class Tablero;
class Pieza;

class HechizoBase
{
public:
	virtual ~HechizoBase() {}

	virtual bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) = 0;
	virtual std::string getNombre() const = 0;
	virtual std::string getMensajeSeleccion() const = 0;
	virtual std::string getMensajeExito() const = 0;
};