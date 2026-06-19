#pragma once
#include "hechizo.h"

class hechizoShiftTime : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "SHIFT_TIME"; }
};

